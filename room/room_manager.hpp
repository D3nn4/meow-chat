#ifndef _ROOM_MANAGER_HPP_
#define _ROOM_MANAGER_HPP_

#include <string>
#include <vector>
// #include "user.hpp"
#include "room.hpp"
#include <memory>


class RoomManager
{
public:

    void createRoom(std::string name, User creator);
    void deleteRoom(std::string name);
    void addUser(std::string name, User newUser);
    void removeUser(std::string name, User user);
// private:

    std::map<std::string, std::shared_ptr<Room> > rooms;

};
#endif //_ROOM_MANAGER_HPP_
