#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>

class ServerCommunicator{
    public:
        ServerCommunicator(){
            ServerMessage message = serverLink.readFromServer();
            if(message.messageTarget == 0 && message.messageRead == 0){
                serverLink.readMessage();
            }
        }

        SharedMemmoryCommunicator getServerLink(){
            return serverLink;
        }

        void writeToServer(int operationCode, double argument1, double argument2,int messageId,double result){
            ServerMessage newMessage = serverLink.readFromServer();
            newMessage.messageId = messageId;
            newMessage.operationCode = operationCode;
            newMessage.arguments[0] = argument1;
            newMessage.arguments[1] = argument2;
            newMessage.result = result;
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