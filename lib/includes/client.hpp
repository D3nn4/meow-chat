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

    // run client only if func ptr set and empty msg sent to get pseudo
    void runClient()
    {
        if(displayMsg_ && displayUsers_) {
                connect();
        }
        createMsg("");
    }

    // set func ptr to interact with ui
    void setReadCallback(std::function<void(std::string)> funcMsg,
                         std::function<void(std::vector<std::string>)>funcUsers)
    {
        displayMsg_ = funcMsg;
        displayUsers_ = funcUsers;
        runClient();
    }

    //func called by ui, when getting entry, creating the Message object
    void createMsg(std::string entry)
    {
        if(entry[0] != '/'){
            Message msg;
            //TODO do by real rooms
            msg.room = "default";
            msg.sender = pseudo;
            msg.bodyLength = entry.size();
            msg.msg = entry;
            msg.encodeHeader(Message::Type::TEXTMSG);
            write(msg);
        }
    }

private:

    //boost post service to send msg
    void write(const Message& msg)
    {
        io_service_.post([this, msg]() {
            bool writeInProgress = !msgQueue_.empty();
            msgQueue_.push_back(msg);
            if (!writeInProgress) {
                sendMsg();
            }
        });
    }


    //connect to server socket
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

    //getting msg (event in async read), trying to decode header
    void readHeader()
    {
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
                                        }
                                    }
                                    else {
                                        std::cout << "error readHeader:" << ec.message() << std::endl;
                                        socket_.close();
                                    }
                                });
    }

    //reading body and decoding body. doing action depending Message::Type
    void readBody()
    {
        // std::cout << "begin read body\n";
        boost::asio::async_read(socket_,
                                boost::asio::buffer(newMsg_.body(), newMsg_.bodyLength),
                                [this](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec) {
                                        Message::Type type = newMsg_.decodeBody();
                                        if(type == Message::Type::TEXTMSG
                                           &&!newMsg_.msg.empty()) {
                                            std::string toDisplay = newMsg_.sender + ": " + newMsg_.msg;
                                            displayMsg_(toDisplay);
                                        }
                                        else if (type == Message::Type::USERLIST){
                                            displayUsers_(newMsg_.getUserList());
                                        }
                                        newMsg_.emptyMe();
                                        readHeader();
                                    }
                                    else {
                                        std::cout << "error readBody:" << ec.message() << std::endl;
                                        socket_.close();
                                    }
                                });
    }

    //send encoded msg to server, from the message queue filled by write()
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
    std::function<void(std::vector<std::string>)> displayUsers_;
};
