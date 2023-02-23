#include <gtest/gtest.h>
#include"../../src/coreLogic/commsProtocol.cpp"
#include <sys/ipc.h>
#include <sys/shm.h>

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

    ServerMessage message;
    message.messageId = 10;
    message.operationCode = 2;
    message.arguments[0] = 1;
    message.arguments[1] = 4;
    message.messageTarget = 0;
    message.result = 15;

    communicator.writeToServer(message.messageId,message.operationCode,message.arguments[0],
        message.arguments[1],message.messageTarget,message.result);

    EXPECT_TRUE(message == communicator.readFromServer());
}

TEST(SharedMemmory,CreatesWithRightExecutor){
    SharedMemmoryCommunicator client(0);
    SharedMemmoryCommunicator server(1);
    EXPECT_EQ(0,client.getExecuter());
    EXPECT_EQ(1,server.getExecuter());
}

TEST(SharedMemmory,WritesUnreadMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.writeToServer(0,0,1,1,0,0);
    EXPECT_EQ(0,communicator.readFromServer().messageRead);
}

TEST(SharedMemmory,ReadMessageReadsMessage){
    SharedMemmoryCommunicator communicator(0);
    communicator.writeToServer(0,0,1,1,0,0);
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