#include "coreLogic/commsProtocol.h"
#include "coreLogic/Writer.h"
#include "spdlog/spdlog.h"


void Writer::operator()(int reciver,ProtectedQueue<ServerMessage> &messages, int &running){
    spdlog::info("Starting Writer Thread");
    SharedMemmoryCommunicator serverLink(reciver);
    while(running){
        if(!messages.empty()){
            if(serverLink.readFromServer().messageRead == 1){
                ServerMessage message = messages.front();
                message.messageTarget = reciver;
                serverLink.writeToServer(message);
                messages.pop();
            }
        }
    }
}