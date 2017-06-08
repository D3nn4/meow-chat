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

    void write(const Message& msg)
    {
        io_service_.post([this, msg]() {
                    sendMsg(msg);
        });
    }

private:

    void accept()
    {
        auto acceptCallback =
            [this](boost::system::error_code ec) {
                if (!ec) {
                    std::string index = std::to_string(nameIndex_);
                    std::string pseudo = "Anonyme" + index;
                    nameIndex_++;
                    User::Ptr newUser = userManager_.createUser(pseudo, std::move(socket_));
                    for(auto room: newUser->joinedRooms){
                      write(userManager_.createUserListMsg(room));
                    }
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
    void readHeader(User::Ptr user)
    {
      // TODO change user en class with getBuffer etc
      user->message.emptyMe();
      boost::asio::async_read(user->socket,
                              boost::asio::buffer(user->message.buff, Message::headerLength),
                              [this, user](boost::system::error_code ec, std::size_t) {
                                if(!ec && user->message.decodeHeader()) {
                                  readBody(user);
                                }
                                else if(ec == boost::asio::error::eof){
                                  ////////////////
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

    void sendMsg(const Message& msg) {
      // std::cout << "in send Message\n";
      // std::cout << "msg room : " << msg.room << std::endl;
        Room::Ptr room = userManager_.roomManager.rooms[msg.room];
        // std::cout << "after geting room ptr\n";
        if(!room->userList.empty()) {
            for(const std::string& user: room->userList){
              std::cout << "message " << msg.encodedMsg << " broadcast to " << user << std::endl;
              boost::asio::async_write(userManager_.users[user]->socket,
                                       boost::asio::buffer(msg.encodedMsg,
                                                           msg.encodedMsg.size()),
                                       [this](boost::system::error_code ec, std::size_t /*length*/) {
                                         // if (!ec) {
                                         // }
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
