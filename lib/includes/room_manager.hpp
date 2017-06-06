#ifndef _ROOM_MANAGER_HPP_
#define _ROOM_MANAGER_HPP_

#include <string>
#include <vector>
// #include "user.hpp"
#include "room.hpp"
#include <memory>
#include <map>


class RoomManager
{
public:

    typedef std::unique_ptr<RoomManager> Ptr;
    
    RoomManager();
    void createRoom(std::string name, std::string creator);
    void deleteRoom(std::string name);
    void addUser(std::string name, std::string newUser);
    void removeUser(std::string name, std::string user);
    void updateUsername(std::string currentName, std::string newName);
// private:

    std::map<std::string, Room::Ptr> rooms;

};
#endif //_ROOM_MANAGER_HPP_
