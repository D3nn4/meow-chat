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
    users.erase(pseudo);
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