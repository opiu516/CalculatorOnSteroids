#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "spdlog/spdlog.h"


struct ServerMessage{
    int messageTarget;
    int messageId;
    int arguments[2];
    int operationCode;
    int messageRead = 0;
    int lastMessageId = 0;
};

bool operator !=(const ServerMessage value1,const ServerMessage value2){
    return value1.messageTarget != value2.messageTarget ||
        value1.messageId != value2.messageId;
}

class Communicator{
    public:
        Communicator(){};
        ~Communicator(){};
        virtual void writeToServer(int messageId,int operationCode,int argument1, int argument2,int messageTarget) = 0;
        virtual ServerMessage readFromServer() = 0;
};


class SharedMemmoryCommunicator{
    public: 
        SharedMemmoryCommunicator(int executer){
            this->executer = executer;

            // ftok to generate unique key
            key_t key = ftok("something",65);
  
             // shmget returns an identifier in shmid
            shmid = shmget(key,1024,0666|IPC_CREAT);
  
            // shmat to attach to shared memory
            sharedMemmory = (ServerMessage*) shmat(shmid,(void*)0,0);
        }
        ~SharedMemmoryCommunicator(){
            shmdt(sharedMemmory);
            if(executer == 1){
                shmctl(shmid,IPC_RMID,NULL);
            }
        }

        void writeToServer(int messageId,int operationCode,int argument1, int argument2,int messageTarget){
            //while(sharedMemmory->messageRead == 0){
                //spdlog::info("{}",sharedMemmory->messageRead);
            //}
            sharedMemmory->messageRead = 0;
            sharedMemmory->messageTarget = messageTarget;
            sharedMemmory->messageId = messageId;
            sharedMemmory->operationCode = operationCode;
            sharedMemmory->arguments[0] = argument1;
            sharedMemmory->arguments[1] = argument2;
        }
        ServerMessage readFromServer(){
            return *sharedMemmory;
        }

        int getExecuter(){
            return executer;
        }

        void readMessage(){
            sharedMemmory->messageRead = 1;
        }

        int getMessageId(){
            sharedMemmory->lastMessageId++;
            return sharedMemmory->lastMessageId;
        }

    private:
        ServerMessage *sharedMemmory;
        int executer;
        int shmid;

};
