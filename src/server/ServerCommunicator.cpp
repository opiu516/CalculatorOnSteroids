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

ProtectedQueue<ServerMessage>& ServerCommunicator::getMessages(){
    return messages;
}

void ServerCommunicator::proccesInput(ProtectedQueue<ServerMessage>& queue1, 
    ProtectedQueue<ServerMessage>& queue2, ProtectedQueue<ServerMessage>& queue3,ServerMessage message){
        spdlog::info("id {}, type{}",message.messageId,message.operationCode);
        if(message.operationCode == ADDITION || message.operationCode == DIFFERENCE){
            queue1.push(message);
        }
        if(message.operationCode == MULTIPLY || message.operationCode == DIVISION){
            queue2.push(message);
        }
        if(message.operationCode == CONCATENATE){
            queue3.push(message);
        }
        readMessage();
}

void ServerCommunicator::firstThread(ProtectedQueue<ServerMessage>& queue){
    if(!queue.empty()){
    ServerMessage message = queue.front();
    double result;
    if(message.operationCode == DIFFERENCE){
        result = message.arguments[0] - message.arguments[1];
    }
    else{
        result = message.arguments[0] + message.arguments[1];
    }
    writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
    queue.pop();
    }
}
void ServerCommunicator::secondThread(ProtectedQueue<ServerMessage>& queue){
    if(!queue.empty()){
        ServerMessage message = queue.front();
        double result;
        if(message.operationCode == DIVISION){
            result = message.arguments[0] / message.arguments[1];
        }
        else{
            result = message.arguments[0] * message.arguments[1];
        }
        writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
        queue.pop();
    }
}
void ServerCommunicator::thirdThread(ProtectedQueue<ServerMessage>& queue){
    if(!queue.empty()){
        ServerMessage message = queue.front();
        double result;
        std::string argument1 = std::to_string((int)message.arguments[0]);
        std::string argument2 = std::to_string((int)message.arguments[1]);
        result = std::stod(argument1 + argument2);
        writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
        queue.pop();
    }
}
