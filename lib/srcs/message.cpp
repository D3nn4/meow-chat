#include "message.hpp"

Message::Message()
    :bodyLength(0)
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
    room = strs[static_cast<int>(Token::ROOM)];
    sender = strs[static_cast<int>(Token::SENDER)];
    msg = strs[static_cast<int>(Token::MSG)];
    int moreMSg = static_cast<int>(Token::MSG) + 1;
    if(strs.size() > moreMSg) {
            for(size_t i = moreMSg; i < strs.size(); i++){
                msg += "/";
                msg += strs[i];
            }
        }
}

std::vector<std::string> Message::getUserList()
{
    return users;
}

void Message::decodeUserList(std::vector<std::string> strs)
{
    if(strs.size() > static_cast<int>(Token::MSG)) {
        auto firstUserIt = strs.begin() + static_cast<int>(Token::MSG); 
        auto lastUserIt = strs.end();
        std::vector<std::string> list(firstUserIt, lastUserIt);
        users = list;
    }
}

Message::Type Message::decodeBody(){
    encodedMsg = buff;
    std::vector<std::string> strs;
    boost::split(strs,encodedMsg,boost::is_any_of("/"));
    //encodedmsg = taille_str/typeMsg/.....
    Type type;
    if(!encodedMsg.empty()
       && !strs.empty()
       && strs.size() >= 2) {
        if(strs[1][0] == static_cast<char>(Type::TEXTMSG)
           && strs.size() > static_cast<int>(Token::MSG)){
            decodeTextMsg(strs);
            type = Type::TEXTMSG;
        }
        else if(strs[1][0] == static_cast<char>(Type::USERLIST)){
                decodeUserList(strs);
                type = Type::USERLIST;
        }
    }
        return type;
}

void Message::encodeHeader(Type type){
    std::string sep = "/";
    std::string str = sep + static_cast<char>(type) + sep+ room + sep + sender + sep + msg;
    std::string size = std::to_string(str.size());
    for(size_t i = size.size(); i < headerLength; i++){
        size.insert(0, "0");
    }
    encodedMsg = size + str;
    std::cout << "encode header: " << encodedMsg << std::endl;
}

void Message::emptyMe(){
    char *end = buff + sizeof(buff);
    std::fill(buff, end, 0);;
    bodyLength = 0;
    room.clear();
    sender.clear();
    msg.clear();
    encodedMsg.clear();
    users.erase(users.begin(), users.end());
    // std::cout << "empty me, buff = " << buff << "empty ?\n";
}
