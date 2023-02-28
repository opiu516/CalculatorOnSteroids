#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include"server/ServerCommunicator.h"
#include "coreLogic/ProtectedQueue.h"
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

TEST(ServerCommunicator,ProccesInputWorks){
    ProtectedQueue<ServerMessage> queue1,queue2,queue3;
    ServerCommunicator comms;
    messageToWrite.operationCode = 1;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    EXPECT_TRUE(queue1.front() == messageToWrite);

    messageToWrite.operationCode = 3;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    EXPECT_TRUE(queue2.front() == messageToWrite);

    messageToWrite.operationCode = 5;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    EXPECT_TRUE(queue3.front() == messageToWrite);
}

TEST(ServerCommunicator,FirstThreadWorks){
    ProtectedQueue<ServerMessage> queue1,queue2,queue3;
    ServerCommunicator comms;

    messageToWrite.operationCode = 1;
    messageToWrite.arguments[0] = 1;
    messageToWrite.arguments[1] = 2;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    comms.firstThread(std::ref(queue1));
    EXPECT_EQ(3,comms.getMessages().front().result);
    comms.getMessages().pop();

    messageToWrite.operationCode = 2;
    messageToWrite.arguments[0] = 3;
    messageToWrite.arguments[1] = 2;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    comms.firstThread(std::ref(queue1));
    EXPECT_EQ(1,comms.getMessages().front().result);
}

TEST(ServerCommunicator,SecondThreadWorks){
    ProtectedQueue<ServerMessage> queue1,queue2,queue3;
    ServerCommunicator comms;

    messageToWrite.operationCode = 3;
    messageToWrite.arguments[0] = 1;
    messageToWrite.arguments[1] = 2;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    comms.secondThread(std::ref(queue2));
    EXPECT_EQ(2,comms.getMessages().front().result);
    comms.getMessages().pop();

    messageToWrite.operationCode = 4;
    messageToWrite.arguments[0] = 3;
    messageToWrite.arguments[1] = 2;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    comms.secondThread(std::ref(queue2));
    EXPECT_EQ(1.5,comms.getMessages().front().result);
}

TEST(ServerCommunicator,ThirdThreadWorks){
    ProtectedQueue<ServerMessage> queue1,queue2,queue3;
    ServerCommunicator comms;

    messageToWrite.operationCode = 5;
    messageToWrite.arguments[0] = 1;
    messageToWrite.arguments[1] = 2;
    comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),messageToWrite);
    comms.thirdThread(std::ref(queue3));
    EXPECT_EQ(12,comms.getMessages().front().result);
}



