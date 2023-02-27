#ifndef commsProtocol_h
#define commsProtocol_h

#include <semaphore.h>

const int CLIENT_ID = 0;
const int SERVER_ID = 1;

struct ServerMessage{
    int messageTarget;
    int messageId;
    double arguments[2];
    double result;
    int operationCode;
    int messageRead = 1;
    int lastMessageId = 0;
};

bool operator !=(const ServerMessage value1,const ServerMessage value2);

bool operator ==(const ServerMessage value1,const ServerMessage value2);


class SharedMemmoryCommunicator{
    public:
        SharedMemmoryCommunicator(int executer);
        ~SharedMemmoryCommunicator();
        void writeToServer(ServerMessage message);
        ServerMessage readFromServer();
        int getExecuter();
        void readMessage();
        int getMessageId();
        void semaphoreWait();
        void semaphorePost();
        int getSemaphoreValue();
        void resetSemaphore();
    private:
        ServerMessage *sharedMemmory;
        int executer;
        int shmid;
        sem_t *semaphore; 
};

#endif