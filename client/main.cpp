#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

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
            // chat_client c(io_service, endpoint_iterator);

            std::thread t([&io_service](){ io_service.run(); });

            int max_msg_length = 512;
            char line[max_body_length + 1];
            while (std::cin.getline(line, max_msg_length + 1))
                {
                    // chat_message msg;
                    // msg.body_length(std::strlen(line));
                    // std::memcpy(msg.body(), line, msg.body_length());
                    // msg.encode_header();
                    // c.write(msg);
                }

            // c.close();
            t.join();
        }
    catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }

    return 0;
}
