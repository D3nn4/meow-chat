#include "uiclient.hpp"
#include <QApplication>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({ "127.0.0.1", "8080" });
    Client c(io_service, endpoint_iterator);


    UiClient w(c);

    std::thread t([&io_service](){io_service.run();});

    w.show();

    a.exec();
    t.join();

    return 0;
}
