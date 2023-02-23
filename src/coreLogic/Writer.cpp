#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>
#include <mutex>

class Writer{
    public:
        void operator()(int reciver,std::queue<ServerMessage> &messages,std::mutex &queueMutex, int &running){
            spdlog::info("Starting Writer Thread");
            SharedMemmoryCommunicator serverLink(reciver);
            while(running){
                sleep(0.2);
                if(!messages.empty()){
                    serverLink.semaphoreWait();
                    std::lock_guard<std::mutex> lock(queueMutex);
                    if(serverLink.readFromServer().messageRead == 1){
                        ServerMessage message = messages.front();
                        serverLink.writeToServer(message.messageId,message.operationCode,message.arguments[0],message.arguments[1],reciver,message.result);
                        messages.pop();
                    }
                    serverLink.semaphorePost();
                }
            }
        }
};