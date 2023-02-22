#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>

class ClientServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink(){
            return serverLink;
        }

        void writeToServer(int operationCode, int argument1, int argument2){
            int messageId = serverLink.getMessageId();
            messageIds.push_back(messageId);
            //spdlog::info("{} - {}",messageIds.back(),messageIds.size());
            ServerMessage newMessage = serverLink.readFromServer();
            newMessage.messageId = messageId;
            newMessage.operationCode = operationCode;
            newMessage.arguments[0] = argument1;
            newMessage.arguments[1] = argument2;
            messages.push(newMessage);
        }

        void process(ServerMessage message){
            spdlog::info("result {}",message.arguments[0]);
            serverLink.readMessage();
        }

        std::vector<int> getMessageIds(){
            return messageIds;
        }

        std::queue<ServerMessage>& getMessages(){
            return messages;
        }

        bool IdContained(int id){
            return std::find(messageIds.begin(), messageIds.end(), id) != messageIds.end();
        }

    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(0);
        std::vector<int> messageIds;
        std::queue<ServerMessage> messages;

};