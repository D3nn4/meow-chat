#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>
#include <set>
#include <boost/asio.hpp>
#include "room.hpp"

using boost::asio::ip::tcp;
struct Room;

struct User
{
    // enum class Role
    // {
    //     ADMIN,
    //     USER,
    //     BAN
    // };
    User(const std::string& name, tcp::socket&& sock)
        :pseudo(name),
         socket(std::move(sock)){}
    ~User(){socket.close();}
    std::string pseudo;
    tcp::socket socket;
    // std::map<std::string, Role> roleByServ;
    std::set<std::string> joinedRooms;
};

#endif //_USER_HPP_
