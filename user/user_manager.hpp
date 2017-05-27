#ifndef _USER_MANAGER_HPP_
#define _USER_MANAGER_HPP_

#include <string>
#include <map>
#include <memory>
#include "user.hpp"
#include "room.hpp"

class UserManager
{
public:

    void createUser(std::string name);
    void deleteUser(std::string name);
    void joinRoom(std::string roomName, User user);
    void quitRoom(std::string roomName, User user);

    // private:

    std::map<std::string, std::shared_ptr<User> > users;

};
#endif //_USER_MANAGER_HPP_
