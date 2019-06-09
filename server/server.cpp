#include <iostream>
#include <cstdlib>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <vector>
#include "user_manager.hpp"
#include "room_manager.hpp"
#include "message.hpp"

using boost::asio::ip::tcp;

class Server
{
    typedef std::deque<Message> messageQueue;

public:
    Server(boost::asio::io_service& io_service,
           const tcp::endpoint& endpoint,
           UserManager& userManager)
        : io_service_(io_service),
          acceptor_(io_service, endpoint),
          socket_(io_service),
          userManager_(userManager),
          nameIndex_(0)
    {
        accept();
    }

  //post need to send
    void write(const Message& msg)
    {
        io_service_.post([this, msg]() {
                    sendMsg(msg);
        });
    }

private:

  //accept new client, create new user with socket given
    void accept()
    {
        auto acceptCallback =
            [this](boost::system::error_code ec) {
                if (!ec) {
                    std::string index = std::to_string(nameIndex_);
                    std::string pseudo = "Anonyme" + index;
                    nameIndex_++;
                    User::Ptr newUser = userManager_.createUser(pseudo, std::move(socket_));
                    std::cout << "newUser.\n";
                    readHeader(newUser);
                }
                else{
                    std::cout << "error accept:" << ec.message() << std::endl;
                }
                accept();
            };

        acceptor_.async_accept(socket_,acceptCallback);

    }

  // wait for event to read on socket
    void readHeader(User::Ptr user)
    {
      // TODO change user en class with getBuffer etc
      user->message.emptyMe();
      boost::asio::async_read(user->socket,
                              boost::asio::buffer(user->message.buff, Message::headerLength),
                              [this, user](boost::system::error_code ec, std::size_t) {
                                //if no error on reading socket and header valid, go read body
                                if(!ec) {
                                  if(user->message.decodeHeader()) {
                                      readBody(user);
                                    }
                                }
                                //if eof (client gone), delete user and stop loop async
                                else if(ec == boost::asio::error::eof){
                                  std::set<std::string> rooms = user->joinedRooms;
                                  userManager_.deleteUser(user->pseudo);
                                  for(auto room: rooms){
                                    write(userManager_.createUserListMsg(room));
                                  }
                                }
                                else{
                                  std::cout << "error readHeader:" << ec.message() << std::endl;
                                      readHeader(user);
                                }
                              });
    }

  //with header giving length of str, get and decode body. if new pseudo, change it and send msg
  //TODO send back msg only if Message::Type::TextMsg
    void readBody(User::Ptr user)
    {
        Message& msg = user->message;
        boost::asio::async_read(
                                user->socket,
                                boost::asio::buffer(msg.body(), msg.bodyLength),
                                [this, user](boost::system::error_code ec, std::size_t) {
                                    if(!ec) {
                                        user->message.decodeBody();
                                        if(user->pseudo.compare(user->message.sender) != 0){
                                            userManager_.updateUsername(user->pseudo, user->message.sender);
                                            for(auto room: user->joinedRooms){
                                                write(userManager_.createUserListMsg(room));
                                            }
                                        }
                                        write(user->message);
                                    }
                                    else{
                                        std::cout << "error readBody:" << ec.message() << std::endl;
                                    }
                                    readHeader(user);
                                });
    }

  //for each user in msg.room, send msg
    void sendMsg(const Message& msg) {
        Room::Ptr room = userManager_.roomManager.rooms[msg.room];
        if(!room->userList.empty()) {
            for(const std::string& user: room->userList){
              std::cout << "message " << msg.encodedMsg << " broadcast to " << user << std::endl;
              boost::asio::async_write(userManager_.users[user]->socket,
                                       boost::asio::buffer(msg.encodedMsg,
                                                           msg.encodedMsg.size()),
                                       [this](boost::system::error_code ec, std::size_t /*length*/) {
                                         if(ec){
                                           std::cout << "error broadcast:" << ec.message() << std::endl;
                                         }
                                       });
            }
        }
    }

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    UserManager& userManager_;
    int nameIndex_;
};

//----------------------------------------------------------------------
