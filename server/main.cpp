#include <iostream>
#include <cstdlib>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <vector>
#include "user_manager.hpp"
#include "room_manager.hpp"
#include "server.cpp"

int main(int argc, char* argv[])
{
    try
        {
            if (argc < 2)
                {
                    std::cerr << "Usage: Server <port> [<port> ...]\n";
                    return 1;
                }
            RoomManager roomManager;
            UserManager userManager(roomManager);
            boost::asio::io_service io_service;
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
            Server server(io_service, endpoint, userManager);

            io_service.run();
        }
    catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }

    return 0;
}
