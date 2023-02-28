#ifndef ServerCommunicator_h
#define ServerCommunicator_h

#include "coreLogic/commsProtocol.h"
#include "coreLogic/ProtectedQueue.h"

const int ADDITION = 1;
const int DIFFERENCE = 2;
const int MULTIPLY = 3;
const int DIVISION = 4;
const int CONCATENATE = 5;

class ServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink();
        void writeToServer(int operationCode, double argument1, double argument2,int messageId,double result);
        void readMessage();
        ProtectedQueue<ServerMessage>& getMessages();
        void proccesInput(ProtectedQueue<ServerMessage>& queue1, ProtectedQueue<ServerMessage>& queue2,
             ProtectedQueue<ServerMessage>& queue3,ServerMessage message);

        void firstThread(ProtectedQueue<ServerMessage>& queue);
        void secondThread(ProtectedQueue<ServerMessage>& queue);
        void thirdThread(ProtectedQueue<ServerMessage>& queue);

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(SERVER_ID);
        ProtectedQueue<ServerMessage> messages;

};

#endif