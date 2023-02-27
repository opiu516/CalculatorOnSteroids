#ifndef ClientServerCommunicator_h
#define ClientServerCommunicator_h

#include<vector>
#include "coreLogic/ProtectedQueue.h"
#include<mutex>
#include "coreLogic/commsProtocol.h"

class ClientServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink();
        void writeToServer(int operationCode, double argument1, double argument2);
        void process(ServerMessage message);
        std::vector<int> getMessageIds();
        ProtectedQueue<ServerMessage>& getMessages();
        bool IdContained(int id);
        void readMessage();

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(CLIENT_ID);
        std::vector<int> messageIds;
        ProtectedQueue<ServerMessage> messages;
        std::mutex idMutex;
};

#endif