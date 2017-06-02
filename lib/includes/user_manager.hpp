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

    typedef std::unique_ptr<UserManager> Ptr;
    
    UserManager(RoomManager& manager)
        :roomManager(manager){}
    User::Ptr createUser(std::string pseudo,tcp::socket&& socket);
    void deleteUser(std::string pseudo);
    void joinRoom(std::string roomName, std::string user);
    void quitRoom(std::string roomName, std::string user);

    // private:

    RoomManager& roomManager;
    std::map<std::string, std::shared_ptr<User> > users;

};
#endif //_USER_MANAGER_HPP_
