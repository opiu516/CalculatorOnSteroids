#include"../coreLogic/commsProtocol.cpp"
#include"../coreLogic/Detector.cpp"
#include"../coreLogic/Writer.cpp"
#include "ServerCommunicator.cpp"
#include <unistd.h>
#include <thread>
#include "spdlog/spdlog.h"
#include <mutex>
#include <string>


int main(){
    ServerCommunicator comms;
    std::queue<ServerMessage> queue1,queue2,queue3;
    std::mutex queue1Mutex;
    std::mutex queue2Mutex;
    std::mutex queue3Mutex;
    std::mutex writingCueueMutex;


    int running = 1;
    std::thread detector(Detector(),1,[&queue1,&queue2,&queue3,&comms,
        &queue1Mutex,&queue2Mutex,&queue3Mutex]
        (ServerMessage message){
        spdlog::info("id {}, type{}",message.messageId,message.operationCode);
        if(message.operationCode == 1 || message.operationCode == 2){
            std::lock_guard<std::mutex> lock(queue1Mutex);
            queue1.push(message);
        }
        if(message.operationCode == 3 || message.operationCode == 4){
            std::lock_guard<std::mutex> lock(queue2Mutex);
            queue2.push(message);
        }
        if(message.operationCode == 5){
            std::lock_guard<std::mutex> lock(queue3Mutex);
            queue3.push(message);
        }
        comms.readMessage();       
    },std::ref(running));

    std::thread writer(Writer(),0,std::ref(comms.getMessages()),std::ref(writingCueueMutex),std::ref(running));

    std::thread thread1([&comms,&queue1,&queue1Mutex,&writingCueueMutex](){
        while(true){
            sleep(0.2);
            if(!queue1.empty()){
                std::lock_guard<std::mutex> lockRead(queue1Mutex);
                std::lock_guard<std::mutex> lockWrite(writingCueueMutex);
                ServerMessage message = queue1.front();
                double result;
                if(message.operationCode%2 == 0){
                    result = message.arguments[0] - message.arguments[1];
                }
                else{
                    result = message.arguments[0] + message.arguments[1];
                }
                comms.writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
                queue1.pop();
            }
        }
    });

    std::thread thread2([&comms,&queue2,&queue2Mutex,&writingCueueMutex](){
        while(true){
            sleep(0.2);
            if(!queue2.empty()){
                std::lock_guard<std::mutex> lockRead(queue2Mutex);
                std::lock_guard<std::mutex> lockWrite(writingCueueMutex);
                ServerMessage message = queue2.front();
                double result;
                if(message.operationCode%2 == 0){
                    result = message.arguments[0] / message.arguments[1];
                }
                else{
                    result = message.arguments[0] * message.arguments[1];
                }
                comms.writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
                queue2.pop();
            }
        }
    });

        std::thread thread3([&comms,&queue3,&queue3Mutex,&writingCueueMutex](){
        while(true){
            sleep(0.2);
            if(!queue3.empty()){
                std::lock_guard<std::mutex> lockRead(queue3Mutex);
                std::lock_guard<std::mutex> lockWrite(writingCueueMutex);
                ServerMessage message = queue3.front();
                double result;
                std::string argument1 = std::to_string((int)message.arguments[0]);
                std::string argument2 = std::to_string((int)message.arguments[1]);
                result = std::stod(argument1 + argument2);
                comms.writeToServer(message.operationCode,message.arguments[0],message.arguments[1],message.messageId,result);
                queue3.pop();
            }
        }
    });


    detector.join();
    return 0;
}