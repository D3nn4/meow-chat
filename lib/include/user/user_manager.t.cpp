#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "user_manager.hpp"

using namespace testing;

class UserManagerTest : public Test
{
public:
    UserManagerTest()
        :userManager(new RoomManager){}
    UserManager userManager;
};

TEST_F(UserManagerTest, CreationNewUser)
{
    std::string pseudo = "Denna";
    userManager.createUser(pseudo);
    EXPECT_THAT(userManager.users.size(), Eq(1));
    EXPECT_THAT(userManager.users.begin()->first, Eq(pseudo));
}

TEST_F(UserManagerTest, DeleteGivenUser)
{
    std::string pseudo = "Denna";
    userManager.createUser(pseudo);
    EXPECT_THAT(userManager.users.size(), Eq(1));
    userManager.deleteUser(pseudo);
    EXPECT_THAT(userManager.users.size(), Eq(0));
}

TEST_F(UserManagerTest, JoinRoom)
{
    std::string pseudo = "Denna";
    std::string room = "kittens";
    userManager.createUser(pseudo);
    EXPECT_THAT(userManager.users[pseudo]->joinedRooms.size(), Eq(0));
    userManager.roomManager->createRoom(room, pseudo);
    userManager.joinRoom(room, pseudo);
    EXPECT_THAT(userManager.users[pseudo]->joinedRooms.size(), Eq(1));
}

TEST_F(UserManagerTest, QuitRoom)
{
    std::string pseudo = "Denna";
    std::string room = "kittens";
    userManager.createUser(pseudo);
    EXPECT_THAT(userManager.users[pseudo]->joinedRooms.size(), Eq(0));
    userManager.roomManager->createRoom(room, pseudo);
    userManager.joinRoom(room, pseudo);
    EXPECT_THAT(userManager.users[pseudo]->joinedRooms.size(), Eq(1));
    userManager.quitRoom(room, pseudo);
    EXPECT_THAT(userManager.users[pseudo]->joinedRooms.size(), Eq(0));
}
