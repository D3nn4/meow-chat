#include "message.hpp"

Message::Message()
    :bodyLength(0),
     room("\0"),
     sender("\0"),
     msg("\0"),
     encodedMsg("\0")
{
    std::fill(buff, (buff + sizeof(buff)), 0);
}

bool Message::decodeHeader()
{
    char header[headerLength + 1] = "";
    std::strncat(header, buff, headerLength);
    header[headerLength] = '\0';
    bodyLength = std::atoi(header);

    if (bodyLength == 0 || bodyLength > maxBodyLength) {
        bodyLength = 0;
        return false;
    }
    return true;
}

char* Message::body()
{
    return buff + headerLength;
}

void Message::decodeTextMsg(std::vector<std::string> strs)
{
    room = strs[static_cast<int>(TextToken::ROOM)];
    sender = strs[static_cast<int>(TextToken::SENDER)];
    msg = strs[static_cast<int>(TextToken::MSG)];
    int moreMSg = static_cast<int>(TextToken::MSG) + 1;
    if(strs.size() > moreMSg) {
            for(size_t i = moreMSg; i < strs.size(); i++){
                msg += "/";
                msg += strs[i];
            }
        }
}

void Message::decodeBody(){
    encodedMsg = buff;
    std::vector<std::string> strs;
    boost::split(strs,encodedMsg,boost::is_any_of("/"));
    //encodedmsg = taille_str/typeMsg/.....
    if(!encodedMsg.empty()
       && !strs.empty()
       && strs.size() > 3) {
        if(strs[1][0] == static_cast<char>(Type::TEXTMSG)
           && strs.size() > static_cast<int>(TextToken::MSG)){
            decodeTextMsg(strs);
        }
        else{
            std::cout << "not textMsg.\n";
        }
    }
}

void Message::encodeHeader(Type type){
    std::string sep = "/";
    std::string str = sep + static_cast<char>(type) + sep+ room + sep + sender + sep + msg;
    std::string size = std::to_string(str.size());
    for(size_t i = size.size(); i < headerLength; i++){
        size.insert(0, "0");
    }
    encodedMsg = size + str;
}

void Message::emptyMe(){
    char *end = buff + sizeof(buff);
    std::fill(buff, end, 0);;
    bodyLength = 0;
    room.clear();
    sender.clear();
    msg.clear();
    encodedMsg.clear();
}
