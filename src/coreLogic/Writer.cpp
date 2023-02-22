#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>

class Writer{
    public:
        void operator()(int reciver,std::queue<ServerMessage> &messages){
            spdlog::info("Starting Writer Thread");
            SharedMemmoryCommunicator serverLink(reciver);
            while(running){
                sleep(0.2);
                if(!messages.empty()){
                    if(serverLink.readFromServer().messageRead == 1){
                        spdlog::info("writing stuff");
                        ServerMessage message = messages.front();
                        serverLink.writeToServer(message.messageId,message.operationCode,message.arguments[0],message.arguments[1],reciver);
                        messages.pop();
                    }
                }
            }
        }
    private:
        int running= 1;

};