#include "uiclient.hpp"
#include <QApplication>
#include <iostream>

using boost::asio::ip::tcp;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({ "127.0.0.1", "4242" });
    std::thread t;
    {
    Client c(io_service, endpoint_iterator);


    UiClient w(c);


    t = std::thread{([&io_service](){io_service.run();})};

    w.show();
    std::cout << "after w.show()\n";
    a.exec();
    std::cout << "after a.exec()\n";
    }
    t.join();
    std::cout << "after t.join()\n";

    return 0;
}
