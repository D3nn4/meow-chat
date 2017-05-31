#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <string>
#include <cstdbool>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

struct Message
{
    enum{ headerLength = 4 };
    enum{ maxBodyLength = 512 };

    Message()
        :bodyLength(0),
         room("\0"),
         sender("\0"),
         msg("\0"),
         encodedMsg("\0"){
        std::fill(buff, (buff + sizeof(buff)), 0);;
    }

    bool decodeHeader() {
        char header[headerLength + 1] = "";
        std::strncat(header, buff, headerLength);
        header[headerLength] = '\0';
        bodyLength = std::atoi(header);

        if (bodyLength > maxBodyLength) {
            bodyLength = 0;
            return false;
        }
        return true;
    }

    char* body(){
        return buff + headerLength;
    }

    void decodeBody(){
        encodedMsg = buff;
        std::vector<std::string> strs;
        boost::split(strs,encodedMsg,boost::is_any_of("/"));
        if(!encodedMsg.empty()
           && !strs.empty()
           && strs.size() > 3) {
            room = strs[1];
            sender = strs[2];
            msg = strs[3];
            if(strs.size() > 4) {
                for(size_t i = 4; i < strs.size(); i++){
                    msg += "/";
                    msg += strs[i];
                }
            }
        }
    }

    void encodeHeader(){
        std::string str = '/' + room + '/' + sender + '/' + msg;
        std::string size = std::to_string(str.size());
        for(size_t i = size.size(); i < headerLength; i++){
            size.insert(0, "0");
        }
        encodedMsg = size + str;
    }

    void emptyMe(){
        char *end = buff + sizeof(buff);
        std::fill(buff, end, 0);;
        bodyLength = 0;
        room.clear();
        sender.clear();
        msg.clear();
        encodedMsg.clear();
    }

    char buff[headerLength + maxBodyLength];
    int bodyLength;
    std::string room;
    std::string sender;
    std::string msg;
    std::string encodedMsg;
};

#endif //_MESSAGE_HPP_
