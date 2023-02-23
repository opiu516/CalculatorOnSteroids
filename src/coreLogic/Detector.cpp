//#include"commsProtocol.cpp"
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "spdlog/spdlog.h"

class Detector{
    public:
        void operator()(int reciver,std::function<void(ServerMessage)> process,int &running){
            int timeouCounter = 0;
            spdlog::info("Starting Detector Thread");
            SharedMemmoryCommunicator serverLink(reciver);
            ServerMessage lastReadMessage;
            lastReadMessage.messageId = -1;
            while(running){
                ServerMessage currentMessage = serverLink.readFromServer();
                if(currentMessage != lastReadMessage){
                    serverLink.semaphoreWait();
                    timeouCounter = 0;
                    lastReadMessage = currentMessage;
                    if(currentMessage.messageTarget == reciver){
                        process(currentMessage);
                    }
                    serverLink.semaphorePost();
                }
                if(reciver == 1 && serverLink.readFromServer().messageRead == 0){
                    timeouCounter++;
                    if(timeouCounter > 50000){
                        timeouCounter = 0;
                        spdlog::info("{} - Message Timed Out",lastReadMessage.messageId);
                        serverLink.readMessage();
                        serverLink.resetSemaphore();
                    }
                }
                sleep(0.2);
            }
        }
};