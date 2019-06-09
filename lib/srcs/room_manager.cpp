#include <string>
#include "room_manager.hpp"
#include <iostream>
#include <memory>

//creation of the default room of the server and the room manager
RoomManager::RoomManager()
{
    Room::Ptr ptr= std::make_shared<Room>();
    ptr->name = "default";
    rooms["default"] = ptr;
}

void RoomManager::createRoom(std::string name, std::string creator)
{
    if(rooms.find(name) == rooms.end()){
        Room::Ptr ptr= std::make_shared<Room>();
        ptr->name = name;
        rooms[name] = ptr;
        addUser(name, creator);
    }
}

void RoomManager::deleteRoom(std::string name)
{
    //"Are you sure" pop-up
    //add admin
    if(name.compare("default") != 0) {
        rooms.erase(name);
    }
}

void RoomManager::addUser(std::string name, std::string newUser)
{
    Room::Ptr room = rooms[name];
    // if(room.banList.find(newUser.pseudo) != room.banList.end()){
    //     std::cout << "You are ban from this room.\n";
    //     return;
    // }
    // if(newUser.roleByServ.find(name) == newUser.roleByServ.end()){
    //     newUser.roleByServ[name] = User::Role::USER;
    // }
    if(rooms.find(name) != rooms.end()) {
        if(room->userList.find(newUser) == room->userList.end()){
            room->userList.insert(newUser);
        }
    }
    else{
        std::cout << "Room " << name << " do not exist.\n";
    }
}

void RoomManager::removeUser(std::string name, std::string user)
{
    // user.joinedRooms.erase(name); //to do in user
    rooms[name]->userList.erase(rooms[name]->userList.find(user));
}

void RoomManager::updateUsername(std::string currentName, std::string newName)
{
    for(auto roomPair: rooms){
        std::set<std::string>&  userList = roomPair.second->userList;
        auto userIt = userList.find(currentName);
        if(userIt != userList.end()){
            userList.insert(newName);
            userList.erase(currentName);
        }
    }
}
