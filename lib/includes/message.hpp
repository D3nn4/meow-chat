#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <string>
#include <vector>
#include <cstdbool>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

class Message
{
public:

    enum class Type
        {
            TEXTMSG = 'T',
            USERLIST = 'U',
            ROOMLIST = 'R',
            CMD = 'C'
        };

    enum{ headerLength = 4 };
    enum{ maxBodyLength = 512 };

    Message();
    bool decodeHeader();
    char* body();
    void decodeBody();
    void encodeHeader(Message::Type type);
    void emptyMe();

    char buff[headerLength + maxBodyLength];
    int bodyLength;
    std::string room;
    std::string sender;
    std::string msg;
    std::string encodedMsg;

private:

    enum class TextToken
        {
            ROOM = 2,
            SENDER,
            MSG
        };
    void decodeTextMsg(std::vector<std::string> strs);
};

#endif //_MESSAGE_HPP_
