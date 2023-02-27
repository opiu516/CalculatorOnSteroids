#include "coreLogic/commsProtocol.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "spdlog/spdlog.h"


bool operator !=(const ServerMessage value1,const ServerMessage value2){
    return value1.messageTarget != value2.messageTarget ||
        value1.messageId != value2.messageId;
}

bool operator ==(const ServerMessage value1,const ServerMessage value2){
    return value1.messageTarget == value2.messageTarget &&
        value1.messageId == value2.messageId &&
        value1.arguments[0] == value2.arguments[0] &&
        value1.arguments[1] == value2.arguments[1] &&
        value1.operationCode == value2.operationCode &&
        value1.result == value2.result;
}


SharedMemmoryCommunicator::SharedMemmoryCommunicator(int executer){
    this->executer = executer;

    key_t key = ftok("memmory",65);
  
    shmid = shmget(key,1024,0666|IPC_CREAT);
  
    sharedMemmory = (ServerMessage*) shmat(shmid,(void*)0,0);

    semaphore = sem_open("semaphore", O_CREAT, 0644, 1);
}

SharedMemmoryCommunicator::~SharedMemmoryCommunicator(){
    shmdt(sharedMemmory);
    sem_close(semaphore);
    if(executer == 1){
        shmctl(shmid,IPC_RMID,NULL);
    }
}

void SharedMemmoryCommunicator::writeToServer(ServerMessage message){
    sharedMemmory->messageRead = 0;
    sharedMemmory->messageTarget = message.messageTarget;
    sharedMemmory->messageId = message.messageId;
    sharedMemmory->operationCode = message.operationCode;
    sharedMemmory->arguments[0] = message.arguments[0];
    sharedMemmory->arguments[1] = message.arguments[1];
    sharedMemmory->result = message.result;
}

ServerMessage SharedMemmoryCommunicator::readFromServer(){
    return *sharedMemmory;
}

int SharedMemmoryCommunicator::getExecuter(){
    return executer;
}

void SharedMemmoryCommunicator::readMessage(){
    sharedMemmory->messageRead = 1;
}

int SharedMemmoryCommunicator::getMessageId(){
    sharedMemmory->lastMessageId++;
    return sharedMemmory->lastMessageId;
}

void SharedMemmoryCommunicator::semaphoreWait(){
    sem_wait(&(*semaphore));
}

void SharedMemmoryCommunicator::semaphorePost(){
    sem_post(&(*semaphore));
}

int SharedMemmoryCommunicator::getSemaphoreValue(){
    int value;
    sem_getvalue(&(*semaphore), &value);
    return value;
}

void SharedMemmoryCommunicator::resetSemaphore(){
    if(getSemaphoreValue() == 0){
        semaphorePost();
    }
}
