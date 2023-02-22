#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>

class ServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink(){
            return serverLink;
        }

        void writeToServer(int operationCode, int argument1, int argument2,int messageId){
            ServerMessage newMessage = serverLink.readFromServer();
            newMessage.messageId = messageId;
            newMessage.operationCode = operationCode;
            newMessage.arguments[0] = argument1;
            newMessage.arguments[1] = argument2;
            messages.push(newMessage);
        }

        void readMessage(){
            serverLink.readMessage();
        }

        std::queue<ServerMessage>& getMessages(){
            return messages;
        }

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(1);
        std::queue<ServerMessage> messages;

};