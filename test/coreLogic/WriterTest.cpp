#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include "coreLogic/Writer.h"
#include "coreLogic/ProtectedQueue.h"



TEST(Writer,WritesMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.readMessage();    
    int running = 1;
    ProtectedQueue<ServerMessage> toWrite;

    std::thread writer(Writer(),0,std::ref(toWrite),std::ref(running));
    {
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
    ProtectedQueue<ServerMessage> toWrite;

    std::thread writer(Writer(),0,std::ref(toWrite),std::ref(running));
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