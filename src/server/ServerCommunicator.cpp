#include "spdlog/spdlog.h"
#include <algorithm>
#include "server/ServerCommunicator.h"

SharedMemmoryCommunicator ServerCommunicator::getServerLink(){
    return serverLink;
}

void ServerCommunicator::writeToServer(int operationCode, double argument1, double argument2,int messageId,double result){
    ServerMessage newMessage = serverLink.readFromServer();
    newMessage.messageId = messageId;
    newMessage.operationCode = operationCode;
    newMessage.arguments[0] = argument1;
    newMessage.arguments[1] = argument2;
    newMessage.result = result;
    messages.push(newMessage);
}

void ServerCommunicator::readMessage(){
    serverLink.readMessage();
}

std::queue<ServerMessage>& ServerCommunicator::getMessages(){
    return messages;
}
