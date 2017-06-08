#include <string>
#include <map>
#include <iostream>
#include "user_manager.hpp"


User::Ptr UserManager::createUser(std::string pseudo,tcp::socket&& socket)
{
    // if(users.find(name) == users.end()){
    User::Ptr ptr = std::make_shared<User>(pseudo, std::move(socket));
    users[pseudo] = ptr;
    joinRoom("default", pseudo);
    return ptr;
    // }
}

void UserManager::deleteUser(std::string pseudo)
{
    std::cout << "In deleteUser\n";
    auto userIt = users.find(pseudo);
    if(userIt == users.end()){
        std::cout << "No user found\n";
    }
    else {
        for(std::string room: userIt->second->joinedRooms){
            roomManager.removeUser(room, pseudo);
        }
        users.erase(pseudo);
    }
}

void UserManager::joinRoom(std::string roomName, std::string user)
{
    auto it = users.find(user);
    if(it != users.end()){
        it->second->joinedRooms.insert(roomName);
        roomManager.addUser(roomName, user);
    }
    else{
        std::cout << "ERROR: user " << user << " not find.\n";
    }
}

void UserManager::quitRoom(std::string roomName, std::string user)
{
    users[user]->joinedRooms.erase(roomName);
    roomManager.removeUser(roomName, user);
}

void UserManager::updateUsername(std::string currentName, std::string newName)
{
    roomManager.updateUsername(currentName, newName);
    users[newName] = users[currentName];
    users[newName]->pseudo = newName;
    users.erase(currentName);
}

Message UserManager::createUserListMsg(std::string room)
{
    Message userListMsg;
    if(!room.empty()) {
        /////////////
        std::set<std::string> userList = roomManager.rooms[room]->userList;
        for(auto user: userList){
            if(!userListMsg.msg.empty()){
                userListMsg.msg += "/";
            }
            userListMsg.msg += user;
        }
        userListMsg.room = room;
        userListMsg.sender = "server";
        userListMsg.encodeHeader(Message::Type::USERLIST);
    }
    return userListMsg;
}
