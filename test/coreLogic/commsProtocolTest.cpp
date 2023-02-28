#include <gtest/gtest.h>
#include"coreLogic/commsProtocol.h"
#include <sys/ipc.h>
#include <sys/shm.h>

ServerMessage messageToWrite = {
  0,
  11,
  {1,4},
  33,
  2,
};

TEST(SharedMemmory,ReadsCorrect){

    key_t key = ftok("memmory",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
    ServerMessage *sharedMemmory = (ServerMessage*) shmat(shmid,(void*)0,0);

    SharedMemmoryCommunicator communicator(0);
    EXPECT_TRUE(*sharedMemmory == communicator.readFromServer());

    shmdt(sharedMemmory);
}

TEST(SharedMemmory,WritesCorrect){
    SharedMemmoryCommunicator communicator(0);

    communicator.writeToServer(messageToWrite);

    EXPECT_TRUE(messageToWrite == communicator.readFromServer());
}

TEST(SharedMemmory,CreatesWithRightExecutor){
    SharedMemmoryCommunicator client(0);
    SharedMemmoryCommunicator server(1);
    EXPECT_EQ(0,client.getExecuter());
    EXPECT_EQ(1,server.getExecuter());
}

TEST(SharedMemmory,WritesUnreadMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.writeToServer(messageToWrite);
    EXPECT_EQ(0,communicator.readFromServer().messageRead);
}

TEST(SharedMemmory,ReadMessageReadsMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.writeToServer(messageToWrite);
    communicator.readMessage();
    EXPECT_EQ(1,communicator.readFromServer().messageRead);
}

TEST(SharedMemmory,GetsUniqueIds){
    SharedMemmoryCommunicator communicator(0);
    int lastId = 0;
    for(int i = 0;i < 20; i++){
        int currentId = communicator.getMessageId();
       EXPECT_TRUE(currentId > lastId);
       lastId = currentId;
    }
}

TEST(ServerMessage,EqualsOperatorWorksPropperly){
    ServerMessage message1 = messageToWrite;
    EXPECT_TRUE(message1 == messageToWrite);
    message1.messageId = 100;
    EXPECT_FALSE(message1 == messageToWrite);
}

TEST(ServerMessage,NotEqualOperatorWorksPropperly){
    ServerMessage message1 = messageToWrite;
    EXPECT_FALSE(message1 != messageToWrite);
    message1.messageId = 100;
    EXPECT_TRUE(message1 != messageToWrite);
}