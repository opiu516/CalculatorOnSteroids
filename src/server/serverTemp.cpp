#include "coreLogic/commsProtocol.h"
#include "coreLogic/Detector.h"
#include "coreLogic/Writer.h"
#include "server/ServerCommunicator.h"
#include "coreLogic/ProtectedQueue.h"
#include <unistd.h>
#include <thread>
#include "spdlog/spdlog.h"
#include <string>


int main(){
    ServerCommunicator comms;
    ProtectedQueue<ServerMessage> queue1,queue2,queue3;


    int running = 1;
    std::thread detector(Detector(),SERVER_ID,[&queue1,&queue2,&queue3,&comms]
        (ServerMessage message){
            comms.proccesInput(std::ref(queue1),std::ref(queue2),std::ref(queue3),message);
    },std::ref(running));

    std::thread writer(Writer(),CLIENT_ID,std::ref(comms.getMessages()),std::ref(running));

    std::thread thread1([&comms,&queue1](){
        while(true){
            sleep(0.2);
            comms.FirstThread(std::ref(queue1));
        }
    });

    std::thread thread2([&comms,&queue2](){
        while(true){
            sleep(0.2);
            comms.SecondThread(std::ref(queue2));
        }
    });

    std::thread thread3([&comms,&queue3](){
        while(true){
            sleep(0.2);
            comms.ThirdThread(std::ref(queue3));
        }
    });


    detector.join();
    writer.join();
    return 0;
}