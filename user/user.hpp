#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>
#include <map>
#include"room.hpp"

struct Room;

struct User
{
    enum class Role
    {
        ADMIN,
        USER,
        BAN
    };

    std::string pseudo;
    std::map<std::string, Role> roleByServ;
    std::map<std::string, Room> joinedRooms;
};

#endif //_USER_HPP_
