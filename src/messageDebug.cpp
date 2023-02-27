#include "spdlog/spdlog.h"
#include"coreLogic/commsProtocol.h"
#include <iostream>

const int CLOSE_DEBUG = 22;
const int READ_MESSAGE = 1;
const int SEMAPHORE_POST = 2;

int main(){
    SharedMemmoryCommunicator serverLink(1);
    while(true){
        int userChoice;
        std::cin>>userChoice;
        if(userChoice == READ_MESSAGE)
            serverLink.readMessage();
        if(userChoice == SEMAPHORE_POST)
            serverLink.semaphorePost();
        if(userChoice == CLOSE_DEBUG)
            return 0;
        ServerMessage message = serverLink.readFromServer();
        spdlog::info("ID - {}, Target - {}, messageRead - {}, semaphore value - {}",message.messageId,message.messageTarget,message.messageRead,serverLink.getSemaphoreValue());
    }
}