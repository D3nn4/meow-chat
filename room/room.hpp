#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <string>
#include <map>
#include "user.hpp"

struct Room
{
    std::string name;
    std::map<std::string, User> userList;
    std::map<std::string, User> banList;
};

#endif //_ROOM_HPP_
