#ifndef ServerCommunicator_h
#define ServerCommunicator_h

#include "coreLogic/commsProtocol.h"
#include <queue>

class ServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink();
        void writeToServer(int operationCode, double argument1, double argument2,int messageId,double result);
        void readMessage();
        std::queue<ServerMessage>& getMessages();

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(SERVER_ID);
        std::queue<ServerMessage> messages;

};

#endif