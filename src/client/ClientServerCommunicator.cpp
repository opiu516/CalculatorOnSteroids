#include "spdlog/spdlog.h"
#include "client/ClientServerCommunicator.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <mutex>


SharedMemmoryCommunicator ClientServerCommunicator::getServerLink(){
    return serverLink;
}

void ClientServerCommunicator::writeToServer(int operationCode, double argument1, double argument2){
    int messageId = serverLink.getMessageId();
    std::lock_guard<std::mutex> idLock(idMutex);
    messageIds.push_back(messageId);
    ServerMessage newMessage = serverLink.readFromServer();
    newMessage.messageId = messageId;
    newMessage.operationCode = operationCode;
    newMessage.arguments[0] = argument1;
    newMessage.arguments[1] = argument2;
    spdlog::info("action - {} ,arg1 - {} , arg2 - {} , ID - {}",operationCode,argument1,argument2,messageId);
    messages.push(newMessage);
}

void ClientServerCommunicator::process(ServerMessage message){
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
    readMessage();
}

std::vector<int> ClientServerCommunicator::getMessageIds(){
    return messageIds;
}

ProtectedQueue<ServerMessage>& ClientServerCommunicator::getMessages(){
    return messages;
}

bool ClientServerCommunicator::IdContained(int id){
    std::lock_guard<std::mutex> idLock(idMutex);
    return std::find(messageIds.begin(), messageIds.end(), id) != messageIds.end();
}

void ClientServerCommunicator::readMessage(){
    serverLink.readMessage();
}

