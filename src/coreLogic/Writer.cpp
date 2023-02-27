#include "coreLogic/commsProtocol.h"
#include "coreLogic/Writer.h"
#include "spdlog/spdlog.h"


void Writer::operator()(int reciver,std::queue<ServerMessage> &messages,std::mutex &queueMutex, int &running){
    spdlog::info("Starting Writer Thread");
    SharedMemmoryCommunicator serverLink(reciver);
    while(running){
        sleep(0.2);
        if(!messages.empty()){
            serverLink.semaphoreWait();
            std::lock_guard<std::mutex> lock(queueMutex);
            if(serverLink.readFromServer().messageRead == 1){
                ServerMessage message = messages.front();
                message.messageTarget = reciver;
                serverLink.writeToServer(message);
                messages.pop();
            }
            serverLink.semaphorePost();
        }
    }
}