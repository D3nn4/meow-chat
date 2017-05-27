#include <string>
#include <map>
#include "user_manager.hpp"


void UserManager::createUser(std::string pseudo)
{
    // if(users.find(name) == users.end()){
    std::shared_ptr<User> ptr = std::make_shared<User>();
        ptr->pseudo = pseudo;
        users[pseudo] = ptr;
    // }
}

void UserManager::deleteUser(std::string pseudo)
{
    users.erase(pseudo);
}

void UserManager::joinRoom(std::string roomName, std::string user)
{
    users[user]->joinedRooms.insert(roomName);
    roomManager->addUser(roomName, user);
}

void UserManager::quitRoom(std::string roomName, std::string user)
{
    users[user]->joinedRooms.erase(roomName);
    roomManager->removeUser(roomName, user);
}
