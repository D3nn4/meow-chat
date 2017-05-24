#include <string>
#include <iostream>
#include <vector>
#include "room_manager.hpp"
#include <memory>

void RoomManager::createRoom(std::string name, User creator)
{
    if(rooms.find(name) == rooms.end()){
        std::shared_ptr<Room> ptr(new Room);
        ptr->name = name;
        rooms[name] = ptr;
        // creator.roleByServ[name] = User::Role::ADMIN;
        addUser(name, creator);
    }
}

void RoomManager::deleteRoom(std::string name)
{
    //"Are you sure" pop-up
    //add admin
    rooms.erase(name);
}

void RoomManager::addUser(std::string name, User newUser)
{
    std::shared_ptr<Room> room = rooms[name];
    // if(room.banList.find(newUser.pseudo) != room.banList.end()){
    //     std::cout << "You are ban from this room.\n";
    //     return;
    // }
    // if(newUser.roleByServ.find(name) == newUser.roleByServ.end()){
    //     newUser.roleByServ[name] = User::Role::USER;
    // }
    if(room->userList.find(newUser.pseudo) == room->userList.end()){
        // newUser.joinedRooms[name] = room; //to do in user
        room->userList[newUser.pseudo] = newUser;
    }
}

void RoomManager::removeUser(std::string name, User user)
{
    // user.joinedRooms.erase(name); //to do in user
    rooms[name]->userList.erase(user.pseudo);
}
