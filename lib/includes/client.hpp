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
        // std::cout << "\nCreate msg with entry: " << entry << std::endl;
                if(!entry.empty()) {
                    if(entry[0] != '/'){
                        Message msg;
                        //TODO do by real rooms
                        msg.room = "default";
                        msg.sender = pseudo;
                        msg.bodyLength = entry.size();
                        msg.msg = entry;
                        msg.encodeHeader(Message::Type::TEXTMSG);
                        // std::cout << "Msg created with pseudo :" << msg.sender << " and msg : " << msg.msg << std::endl;
                        write(msg);
                    }
                }
    }
    void write(const Message& msg)
    {
        // std::cout << "in write, msg: "<< msg.encodedMsg << std::endl;
        io_service_.post(
                         [this, msg]() {
                             bool writeInProgress = !msgQueue_.empty();
                             msgQueue_.push_back(msg);
                             // std::cout << "msg post: " << msg.encodedMsg << std::endl;
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
                                       else{
                                           std::cout << "error connect:" << ec.message() << std::endl;
                                       }
                                   });
    }

    void readHeader()
    {
        // std::cout << "begin read header\n";
        newMsg_.emptyMe();
        boost::asio::async_read(socket_,
                                boost::asio::buffer(newMsg_.buff, Message::headerLength),
                                [this](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec) {
                                        if(newMsg_.decodeHeader()) {
                                            readBody();
                                        }
                                        else {
                                            std::cout << "PB DECODE HEADER\n";
                                            std::cout << "buffer : " << newMsg_.buff << std::endl;
                                        }
                                    }
                                    else {
                                        std::cout << "error readHeader:" << ec.message() << std::endl;
                                        socket_.close();
                                    }
                                    // std::cout << "end read header\n";
                                });
    }

    void readBody()
    {
        // std::cout << "begin read body\n";
        boost::asio::async_read(socket_,
                                boost::asio::buffer(newMsg_.body(), newMsg_.bodyLength),
                                [this](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec) {
                                        newMsg_.decodeBody();
                                        if(!newMsg_.msg.empty()) {
                                            std::string toDisplay = newMsg_.sender + ": " + newMsg_.msg;
                                            displayMsg_(toDisplay);
                                        }
                                        newMsg_.emptyMe();
                                        readHeader();
                                    }
                                    else {
                                        std::cout << "error readBody:" << ec.message() << std::endl;
                                        socket_.close();
                                    }
                                });
        // std::cout << "end read body\n";
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
                                         std::cout << "error sendMsg:" << ec.message() << std::endl;
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
    Message newMsg_;
    messageQueue msgQueue_;
    std::function<void(std::string)> displayMsg_;
};
