#ifndef _USER_MANAGER_HPP_
#define _USER_MANAGER_HPP_

#include <string>
#include <map>
#include <memory>
#include "user.hpp"
#include "room.hpp"
#include "room_manager.hpp"

class UserManager
{
public:

    UserManager(RoomManager* manager)
        :roomManager(manager){}
    void createUser(std::string pseudo);
    void deleteUser(std::string pseudo);
    void joinRoom(std::string roomName, std::string user);
    void quitRoom(std::string roomName, std::string user);

    // private:

    RoomManager* roomManager;
    std::map<std::string, std::shared_ptr<User> > users;

};
#endif //_USER_MANAGER_HPP_
