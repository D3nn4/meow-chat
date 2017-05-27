#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "room_manager.hpp"

using namespace testing;

class RoomManagerTest : public Test
{
public:
    RoomManager roomManager;
    User userTest;
};


TEST_F(RoomManagerTest, CreateNewRoomNotExisting){
    std::string roomName = "kittens";
    roomManager.createRoom(roomName, "Denna");
    EXPECT_THAT(roomManager.rooms[roomName]->name, Eq(roomName));
    // EXPECT_THAT(userTest.roleByServ[roomName], Eq(User::Role::ADMIN));
}

TEST_F(RoomManagerTest, CreateNewRoomAlreadyExisting){
    std::string roomName = "kittens";
    roomManager.createRoom(roomName, "Denna");
    roomManager.createRoom(roomName, "Denna");
    EXPECT_THAT(roomManager.rooms.size(), Eq(1));
}

TEST_F(RoomManagerTest, JoinExistingRoom){
    std::string roomName = "kittens";
    roomManager.createRoom(roomName, "Denna");
    roomManager.addUser(roomName, "patate");
    // EXPECT_THAT(newUser.joinedRooms.size(), Eq(1));
    // EXPECT_THAT(newUser.joinedRooms.begin()->first, Eq(roomName));
    EXPECT_THAT(roomManager.rooms[roomName]->userList.size(), Eq(2));
}

TEST_F(RoomManagerTest, DeleteRoom){
    std::string roomName = "kittens";
    roomManager.createRoom(roomName, "Denna");
    EXPECT_THAT(roomManager.rooms.size(), Eq(1));
    roomManager.deleteRoom(roomName);
    EXPECT_THAT(roomManager.rooms.size(), Eq(0));
}

TEST_F(RoomManagerTest, QuitAnExistingRoom){
    std::string roomName = "kittens";
    roomManager.createRoom(roomName, "Denna");
    EXPECT_THAT(roomManager.rooms[roomName]->userList.size(), Eq(1));
    roomManager.removeUser(roomName, "Denna");
    EXPECT_THAT(roomManager.rooms[roomName]->userList.size(), Eq(0));
}
