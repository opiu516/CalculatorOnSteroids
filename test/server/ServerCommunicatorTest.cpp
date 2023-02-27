#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include"server/ServerCommunicator.h"
#include <mutex>
#include <queue>
#include <vector>

TEST(ServerCommunicator,AddsMessageToQueue){
    ServerCommunicator communicator;
    communicator.writeToServer(1,10,12,11,15);
    ServerMessage message = communicator.getMessages().front();
    EXPECT_EQ(1,message.operationCode);
    EXPECT_EQ(10,message.arguments[0]);
    EXPECT_EQ(12,message.arguments[1]);
    EXPECT_EQ(11,message.messageId);
    EXPECT_EQ(15,message.result);
}
