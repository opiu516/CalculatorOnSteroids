#include <gtest/gtest.h>
#include "coreLogic/commsProtocolTest.cpp"
#include "coreLogic/WriterTest.cpp"
#include "coreLogic/DetectorTest.cpp"
#include "client/ClientServerCommunicatorTest.cpp"
#include "server/ServerCommunicatorTest.cpp"
#include <iostream>

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}