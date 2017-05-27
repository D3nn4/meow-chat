#include <iostream>
#include <cstdlib>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <vector>
#include "user_manager.hpp"
#include "room_manager.hpp"

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
      nameIndex(0)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
              std::string index = std::to_string(nameIndex);
              std::string pseudo = "Anonyme" + index;
              nameIndex++;
              userManager_.createUser(pseudo, std::move(socket_));
              std::cout << "new client\n";
          }
          else{
              std::cout << "error :" << ec.message() << std::endl;
          }
          do_accept();
        });
  }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    UserManager& userManager_;
    int nameIndex;
};

//----------------------------------------------------------------------

