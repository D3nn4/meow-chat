#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <string>
#include <set>
#include "user.hpp"

struct Room
{
    std::string name;
    std::set<std::string> userList;
    // std::map<std::string, User> banList;
};

#endif //_ROOM_HPP_
