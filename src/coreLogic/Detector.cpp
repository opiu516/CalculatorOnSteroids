//#include"commsProtocol.cpp"
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "spdlog/spdlog.h"

class Detector{
    public:
        void operator()(int reciver,std::function<void(ServerMessage)> process){
            spdlog::info("Starting Detector Thread");
            SharedMemmoryCommunicator serverLink(reciver);
            ServerMessage lastReadMessage;
            lastReadMessage.messageId = -1;
            while(running){
                ServerMessage currentMessage = serverLink.readFromServer();
                if(currentMessage != lastReadMessage){
                    lastReadMessage = currentMessage;
                    if(currentMessage.messageTarget == reciver){
                        process(currentMessage);
                    }
                }
                sleep(0.2);
            }
        }
    private:
        int running= 1;

};