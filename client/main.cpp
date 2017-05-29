#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "client.cpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
        {
            if (argc != 3)
                {
                    std::cerr << "Usage: chat_client <host> <port>\n";
                    return 1;
                }

            boost::asio::io_service io_service;

            tcp::resolver resolver(io_service);
            auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
            Client c(io_service, endpoint_iterator);
            std::cout << "Enter your pseudo :";
            std::cin >> c.pseudo;

            std::thread t([&io_service](){ io_service.run(); });


            
            char line[Message::maxBodyLength+ 1];
            // std::cout << c.pseudo << ": ";
            while (std::cin.getline(line, Message::maxBodyLength + 1))
                {
                    Message msg;
                    //TODO do by real rooms
                    msg.room = "default";
                    msg.sender = c.pseudo;
                    msg.bodyLength = std::strlen(line);
                    msg.msg = line;
                    if(!msg.msg.empty()) {
                        msg.encodeHeader();
                        c.write(msg);
                    }
                    char *end = line + sizeof(line);
                    std::fill(line, end, 0);;
                    // std::cout << c.pseudo << ": ";
                }

            c.close();
            t.join();
        }
    catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }

    return 0;
}
