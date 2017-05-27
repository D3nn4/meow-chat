#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>
#include <set>
#include "room.hpp"

struct Room;

struct User
{
    // enum class Role
    // {
    //     ADMIN,
    //     USER,
    //     BAN
    // };

    std::string pseudo;
    // std::map<std::string, Role> roleByServ;
    std::set<std::string> joinedRooms;
};

#endif //_USER_HPP_
