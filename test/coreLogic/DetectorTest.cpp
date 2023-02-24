#include <gtest/gtest.h>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include"../../src/coreLogic/Detector.cpp"


TEST(Detector, detectsMessage) {
    SharedMemmoryCommunicator communicator(0);
    ServerMessage messageRead;
    int running = 1;

    std::thread detector(Detector(),0,[&messageRead,&running](ServerMessage message){
      messageRead = message;
      running = 0;
    },std::ref(running));

    communicator.writeToServer(messageToWrite);

    detector.join();

    EXPECT_TRUE(messageToWrite == messageRead);

}

TEST(Detector, detectsMessageForTarget) {
    SharedMemmoryCommunicator communicator(0);
    ServerMessage messageRead;
    int running = 1;


    std::thread detector(Detector(),0,[&messageRead,&running](ServerMessage message){
      messageRead = message;
      running = 0;
    },std::ref(running));

    communicator.writeToServer(messageToWrite);

    messageToWrite.messageTarget = 0;
    messageToWrite.result = 10;

    communicator.writeToServer(messageToWrite);

    detector.join();

    EXPECT_TRUE(messageToWrite == messageRead);

}

TEST(Detector, ServerTimesOutUnreadMessages) {
    SharedMemmoryCommunicator communicator(1);
    ServerMessage messageRead;
    int running = 1;

    std::thread detector(Detector(),1,[&messageRead,&running](ServerMessage message){
    },std::ref(running));

    communicator.writeToServer(messageToWrite);

    EXPECT_EQ(0,communicator.readFromServer().messageRead);
    sleep(5);
    EXPECT_EQ(1,communicator.readFromServer().messageRead);

    running = 0;
    detector.join();
}

TEST(Detector, ClientDoesNotTimeOutMessage) {
    SharedMemmoryCommunicator communicator(0);
    ServerMessage messageRead;
    int running = 1;

    std::thread detector(Detector(),0,[&messageRead,&running](ServerMessage message){
    },std::ref(running));

    communicator.writeToServer(messageToWrite);

    EXPECT_EQ(0,communicator.readFromServer().messageRead);
    sleep(5);
    EXPECT_EQ(0,communicator.readFromServer().messageRead);

    running = 0;
    detector.join();
}
