#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "user.hpp"

class Client
{
    typedef std::deque<Message> messageQueue;

public:
    
    std::string pseudo;
    Client(boost::asio::io_service& io_service,
           tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service),
          socket_(io_service)
    {
        connect(endpoint_iterator);
    }

    void createMsg(std::string entry)
    {
                if(!entry.empty()) {
                    Message msg;
                    //TODO do by real rooms
                    msg.room = "default";
                    msg.sender = pseudo;
                    msg.bodyLength = entry.size();
                    msg.msg = entry;
                    msg.encodeHeader();
                    write(msg);
                }
    }
    void write(const Message& msg)
    {
        io_service_.post(
                         [this, msg]() {
                             bool writeInProgress = !msgQueue_.empty();
                             msgQueue_.push_back(msg);
                             if (!writeInProgress) {
                                 sendMsg();
                             }
                         });
    }

    void close()
    {
        io_service_.post([this]() { socket_.close(); });
    }

private:
    void connect(tcp::resolver::iterator endpoint_iterator)
    {
        boost::asio::async_connect(socket_, endpoint_iterator,
                                   [this](boost::system::error_code ec, tcp::resolver::iterator) {
                                       if (!ec) {
                                           readHeader();
                                       }
                                   });
    }

    void readHeader()
    {
        boost::asio::async_read(socket_,
                                boost::asio::buffer(msg_.buff, Message::headerLength),
                                [this](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec && msg_.decodeHeader()) {
                                        readBody();
                                    }
                                    else {
                                        socket_.close();
                                    }
                                });
    }

    void readBody()
    {
        boost::asio::async_read(socket_,
                                boost::asio::buffer(msg_.body(), msg_.bodyLength),
                                [this](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec) {
                                        msg_.decodeBody();
                                        if(!msg_.msg.empty() /* && msg_.sender.compare(pseudo) != 0 */) {
                                            
                                            std::cout << msg_.sender << ": " << msg_.msg << std::endl;
                                            msg_.emptyMe();
                                        }
                                        readHeader();
                                    }
                                    else {
                                        socket_.close();
                                    }
                                });
    }

    void sendMsg()
    {
        boost::asio::async_write(socket_,
                                 boost::asio::buffer(msgQueue_.front().encodedMsg,
                                                     msgQueue_.front().encodedMsg.size()),
                                 [this](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         msgQueue_.pop_front();
                                         if (!msgQueue_.empty()) {
                                             sendMsg();
                                         }
                                     }
                                     else {
                                         socket_.close();
                                     }
                                 });
    }


private:

    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    Message msg_;
    messageQueue msgQueue_;
};
