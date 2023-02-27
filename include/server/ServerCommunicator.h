#ifndef ServerCommunicator_h
#define ServerCommunicator_h

#include "coreLogic/commsProtocol.h"
#include "coreLogic/ProtectedQueue.h"

class ServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink();
        void writeToServer(int operationCode, double argument1, double argument2,int messageId,double result);
        void readMessage();
        ProtectedQueue<ServerMessage>& getMessages();
        void proccesInput(ProtectedQueue<ServerMessage>& queue1, ProtectedQueue<ServerMessage>& queue2,
             ProtectedQueue<ServerMessage>& queue3,ServerMessage message);

        void FirstThread(ProtectedQueue<ServerMessage>& queue);
        void SecondThread(ProtectedQueue<ServerMessage>& queue);
        void ThirdThread(ProtectedQueue<ServerMessage>& queue);

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(SERVER_ID);
        ProtectedQueue<ServerMessage> messages;

};

#endif