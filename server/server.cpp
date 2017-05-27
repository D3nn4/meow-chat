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
public:
  Server(boost::asio::io_service& io_service,
         const tcp::endpoint& endpoint,
         UserManager& userManager)
    : acceptor_(io_service, endpoint),
      socket_(io_service),
      userManager_(userManager),
      nameIndex_(0)
  {
    accept();
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
                    std::cout << "new client\n";
                    read(newUser);
                }
                else{
                    std::cout << "error accept:" << ec.message() << std::endl;
                }
                accept();
            };

        acceptor_.async_accept(socket_,acceptCallback);

    }
    void read(User::Ptr user)
    {
        // TODO change user en class with getBuffer etc
        boost::asio::async_read(user->socket,
                                boost::asio::buffer(user->message.buff, Message::headerLength),
                                [this, user](boost::system::error_code ec, std::size_t)
                                {
                                    if(!ec && user->message.decodeHeader()) {
                                        // boost::asio::buffer(user->message.body())
                                        std::cout << "toto\n";
                                    }
                                    else{
                                        std::cout << "error read:" << ec.message() << std::endl;
                                    }
                                });
        //asynch read with callback
        //at end callback readCallback()
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    UserManager& userManager_;
    int nameIndex_;
};

//----------------------------------------------------------------------
