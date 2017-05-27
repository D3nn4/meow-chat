
#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <string>


struct Message
{
    enum{ headerLength = 4 };
    enum{ maxBodyLength = 512 };

    bool decodeHeader() {
        char header[headerLength + 1] = "";
        std::strncat(header, buff, headerLength);
        bodyLength = std::atoi(header);
        if (bodyLength > maxBodyLength) {
            bodyLength = 0;
            return false;
        }
        return true;
    }

    char buff[headerLength + maxBodyLength];
    int bodyLength;
    std::string sender;
    std::string room;
    std::string msg;
};

#endif //_MESSAGE_HPP_
