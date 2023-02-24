#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include"../../src/coreLogic/Writer.cpp"
#include <mutex>
#include <queue>


TEST(Writer,WritesMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.readMessage();    
    int running = 1;
    std::queue<ServerMessage> toWrite;
    std::mutex queueMutex;

    std::thread writer(Writer(),0,std::ref(toWrite),std::ref(queueMutex),std::ref(running));
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        toWrite.push(messageToWrite);
    }
    sleep(1);
    EXPECT_TRUE(messageToWrite == communicator.readFromServer());
    running = 0;
    writer.join();
}

TEST(Writer,WritesOnlyIfMessageIsRead){
    SharedMemmoryCommunicator communicator(0);
    int running = 1;
    std::queue<ServerMessage> toWrite;
    std::mutex queueMutex;

    std::thread writer(Writer(),0,std::ref(toWrite),std::ref(queueMutex),std::ref(running));
    communicator.readMessage();
    toWrite.push(messageToWrite);
    messageToWrite.messageId = 22;
    toWrite.push(messageToWrite);
    EXPECT_TRUE(messageToWrite != communicator.readFromServer());
    sleep(1);
    communicator.readMessage();
    sleep(1);
    EXPECT_TRUE(messageToWrite == communicator.readFromServer());
    running = 0;
    writer.join();
}