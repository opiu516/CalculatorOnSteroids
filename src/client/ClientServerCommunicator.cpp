#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>
#include <mutex>


class ClientServerCommunicator{
    public:
        SharedMemmoryCommunicator getServerLink(){
            return serverLink;
        }

        void writeToServer(int operationCode, double argument1, double argument2){
            int messageId = serverLink.getMessageId();
            std::lock_guard<std::mutex> idLock(idMutex);
            messageIds.push_back(messageId);
            ServerMessage newMessage = serverLink.readFromServer();
            newMessage.messageId = messageId;
            newMessage.operationCode = operationCode;
            newMessage.arguments[0] = argument1;
            newMessage.arguments[1] = argument2;
            std::lock_guard<std::mutex> messageLock(writingCueueMutex);
            spdlog::info("action - {} ,arg1 - {} , arg2 - {} , ID - {}",operationCode,argument1,argument2,messageId);
            messages.push(newMessage);
        }

        void process(ServerMessage message){
            char sign;
            switch (message.operationCode)
            {
            case 1: sign = '+';
                break;
            case 2: sign = '-';
                break;
            case 3: sign = '*';
                break;
            case 4: sign = '/';
                break;  
            case 5: sign = '&';
                break;          
            default:
                sign = 'N';
                break;
            }
            spdlog::info("{} : {} {} {} = {}",message.messageId,message.arguments[0],sign,message.arguments[1],message.result);
        }

        std::vector<int> getMessageIds(){
            return messageIds;
        }

        std::queue<ServerMessage>& getMessages(){
            return messages;
        }

        bool IdContained(int id){
            std::lock_guard<std::mutex> idLock(idMutex);
            return std::find(messageIds.begin(), messageIds.end(), id) != messageIds.end();
        }

        void readMessage(){
            //spdlog::info("I read");
            serverLink.readMessage();
        }

        std::mutex& getWritingCueueMutex(){
            return writingCueueMutex;
        }


    private:
        SharedMemmoryCommunicator serverLink = SharedMemmoryCommunicator(0);
        std::vector<int> messageIds;
        std::queue<ServerMessage> messages;
        std::mutex writingCueueMutex;
        std::mutex idMutex;

};