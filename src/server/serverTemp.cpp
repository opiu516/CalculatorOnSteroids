#include"../coreLogic/commsProtocol.cpp"
#include"../coreLogic/Detector.cpp"
#include"../coreLogic/Writer.cpp"
#include "ServerCommunicator.cpp"
#include<iostream>
#include <queue>
#include <unistd.h>
#include <thread>
#include <vector>
#include "spdlog/spdlog.h"


int main(){
    ServerCommunicator comms;
    std::queue<ServerMessage> queue1,queue2;

    std::thread detector(Detector(),1,[&queue1,&queue2,&comms](ServerMessage message){
        spdlog::info("id {}, type{}",message.messageId,message.operationCode);
        if(message.operationCode == 1 || message.operationCode == 2){
            spdlog::info("dovai v queue1");
            queue1.push(message);
        }
        if(message.operationCode == 3 || message.operationCode == 4){
            spdlog::info("dovai v queue2");
            queue2.push(message);
        }
        comms.readMessage();       
    });

    std::thread writer(Writer(),0,std::ref(comms.getMessages()));

    std::thread thread1([&comms,&queue1](){
        while(true){
            sleep(0.2);
            if(!queue1.empty()){
                ServerMessage message = queue1.front();
                int result;
                if(message.operationCode%2 == 0){
                    result = message.arguments[0] - message.arguments[1];
                }
                else{
                    result = message.arguments[0] + message.arguments[1];
                }
                comms.writeToServer(0,result,0,message.messageId);
                queue1.pop();
            }
        }
    });

    std::thread thread2([&comms,&queue2](){
        while(true){
            sleep(0.2);
            if(!queue2.empty()){
                ServerMessage message = queue2.front();
                int result;
                if(message.operationCode%2 == 0){
                    result = message.arguments[0] / message.arguments[1];
                }
                else{
                    result = message.arguments[0] * message.arguments[1];
                }
                comms.writeToServer(0,result,0,message.messageId);
                queue2.pop();
            }
        }
    });


    detector.join();
    return 0;
}