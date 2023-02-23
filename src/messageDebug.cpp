#include "spdlog/spdlog.h"
#include"coreLogic/commsProtocol.cpp"

int main(){
    SharedMemmoryCommunicator serverLink(0);
    while(true){
        int temp;
        std::cin>>temp;
        if(temp == 1)
            serverLink.readMessage();
        if(temp == 2)
            serverLink.semaphorePost();
        if(temp == 3)
            serverLink.resetSemaphore();
        ServerMessage message = serverLink.readFromServer();
        spdlog::info("ID - {}, Target - {}, messageRead - {}, semaphore value - {}",message.messageId,message.messageTarget,message.messageRead,serverLink.getSemaphoreValue());
    }
}