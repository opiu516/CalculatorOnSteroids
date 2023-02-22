#include "spdlog/spdlog.h"
#include"coreLogic/commsProtocol.cpp"

int main(){
    SharedMemmoryCommunicator serverLink(0);
    while(true){
        int temp;
        std::cin>>temp;
        if(temp == 1)
            serverLink.readMessage();
        ServerMessage message = serverLink.readFromServer();
        spdlog::info("ID - {}, Target - {}, messageRead - {}",message.messageId,message.messageTarget,message.messageRead);
    }
}