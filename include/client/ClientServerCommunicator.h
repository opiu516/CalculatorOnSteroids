#ifndef ClientServerCommunicator_h
#define ClientServerCommunicator_h

#include<vector>
#include<queue>
#include<mutex>
#include "coreLogic/commsProtocol.h"

class ClientServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink();
        void writeToServer(int operationCode, double argument1, double argument2);
        void process(ServerMessage message);
        std::vector<int> getMessageIds();
        std::queue<ServerMessage>& getMessages();
        bool IdContained(int id);
        void readMessage();
        std::mutex& getWritingCueueMutex();

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(CLIENT_ID);
        std::vector<int> messageIds;
        std::queue<ServerMessage> messages;
        std::mutex writingCueueMutex;
        std::mutex idMutex;
};

#endif