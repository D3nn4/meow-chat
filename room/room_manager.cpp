#include <string>
#include "room_manager.hpp"
#include <memory>

void RoomManager::createRoom(std::string name, std::string creator)
{
    if(rooms.find(name) == rooms.end()){
        std::shared_ptr<Room> ptr= std::make_shared<Room>();
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

void RoomManager::addUser(std::string name, std::string newUser)
{
    std::shared_ptr<Room> room = rooms[name];
    // if(room.banList.find(newUser.pseudo) != room.banList.end()){
    //     std::cout << "You are ban from this room.\n";
    //     return;
    // }
    // if(newUser.roleByServ.find(name) == newUser.roleByServ.end()){
    //     newUser.roleByServ[name] = User::Role::USER;
    // }
    if(room->userList.find(newUser) == room->userList.end()){
        room->userList.insert(newUser);
    }
}

void RoomManager::removeUser(std::string name, std::string user)
{
    // user.joinedRooms.erase(name); //to do in user
    rooms[name]->userList.erase(rooms[name]->userList.find(user));
}
