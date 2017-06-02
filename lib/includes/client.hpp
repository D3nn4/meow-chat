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
           tcp::resolver::iterator& endpoint_iterator)
        : io_service_(io_service),
          endpoint_iterator_(endpoint_iterator),
          socket_(io_service) {}

    ~Client()
    {
        io_service_.post([this]() { socket_.close(); });
    }

    void runClient()
    {
        if(displayMsg_) {
                connect();
        }
    }
    
    void setReadCallback(std::function<void(std::string)> func)
    {
        displayMsg_ = func;
        runClient();
    }
    
    void createMsg(std::string entry)
    {
        std::cout << "Create msg with entry: " << entry << std::endl;
                if(!entry.empty()) {
                    Message msg;
                    //TODO do by real rooms
                    msg.room = "default";
                    msg.sender = pseudo;
                    msg.bodyLength = entry.size();
                    msg.msg = entry;
                    msg.encodeHeader();
                    std::cout << "Msg created with pseudo :" << msg.sender << " and msg : " << msg.msg << std::endl;
                    write(msg);
                }
    }
    void write(const Message& msg)
    {
        std::cout << "in write, msg: "<< msg.encodedMsg << std::endl;
        io_service_.post(
                         [this, msg]() {
                             std::cout << "toto\n";
                             bool writeInProgress = !msgQueue_.empty();
                             msgQueue_.push_back(msg);
                             std::cout << "msg post: " << msg.encodedMsg << std::endl;
                             if (!writeInProgress) {
                                 sendMsg();
                             }
                         });
    }


private:
    void connect()
    {
        boost::asio::async_connect(socket_, endpoint_iterator_,
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
                                            std::string toDisplay = msg_.sender + ": " + msg_.msg;
                                            displayMsg_(toDisplay);
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
    tcp::resolver::iterator& endpoint_iterator_;
    tcp::socket socket_;
    std::thread t_;
    Message msg_;
    messageQueue msgQueue_;
    std::function<void(std::string)> displayMsg_;
};
