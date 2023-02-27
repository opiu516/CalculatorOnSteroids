#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include"client/ClientServerCommunicator.h"
#include "coreLogic/ProtectedQueue.h"
#include <queue>
#include <vector>

TEST(ClientServerCommunicator,AddsMessageToQueue){
    ClientServerCommunicator communicator;
    communicator.writeToServer(1,10,12);
    ServerMessage message = communicator.getMessages().front();
    EXPECT_EQ(1,message.operationCode);
    EXPECT_EQ(10,message.arguments[0]);
    EXPECT_EQ(12,message.arguments[1]);
}

TEST(ClientServerCommunicator,MessagesGetUniqueIds){
    ClientServerCommunicator communicator;
    communicator.writeToServer(1,10,12);
    communicator.writeToServer(1,13,12);
    ServerMessage message1 = communicator.getMessages().front();
    communicator.getMessages().pop();
    ServerMessage message2 = communicator.getMessages().front();
    EXPECT_FALSE(message1.messageId == message2.messageId);
}

TEST(ClientServerCommunicator,AddsMessageIdToVector){
    ClientServerCommunicator communicator;
    communicator.writeToServer(1,10,12);
    ServerMessage message = communicator.getMessages().front();
    EXPECT_EQ(message.messageId,communicator.getMessageIds().front());
}

TEST(ClientServerCommunicator,IdContainedWorksIfIdIsContained){
    ClientServerCommunicator communicator;
    communicator.writeToServer(1,10,12);
    ServerMessage message = communicator.getMessages().front();
    EXPECT_TRUE(communicator.IdContained(message.messageId));
}

TEST(ClientServerCommunicator,IdContainedWorksIfIdIsNotContained){
    ClientServerCommunicator communicator;
    communicator.writeToServer(1,10,12);
    ServerMessage message = communicator.getMessages().front();
    EXPECT_FALSE(communicator.IdContained(message.messageId + 1));
}