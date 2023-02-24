#include"../coreLogic/commsProtocol.cpp"
#include"../coreLogic/Detector.cpp"
#include"../coreLogic/Writer.cpp"
#include "ClientServerCommunicator.cpp"
#include "spdlog/spdlog.h"
#include <thread>
#include <unistd.h>
#include <random>



int main(){
    ClientServerCommunicator comms;
    int running = 1;
    std::thread detector(Detector(),0,[&comms](ServerMessage message){
        if(comms.IdContained(message.messageId)){
            comms.process(message);
            comms.readMessage();
        }
    },std::ref(running));

    std::thread writer(Writer(),1,std::ref(comms.getMessages()),std::ref(comms.getWritingCueueMutex()),std::ref(running));

    for(int i = 1;i<3000000;i++){   
        sleep(0.1);
        int choice = 1 + (std::rand() % static_cast<int>(5 - 1 + 1));
        double arguments[2];
        arguments[0]  = 1 + (std::rand() % static_cast<int>(100 - 1 + 1));
        arguments[1]  = 1 + (std::rand() % static_cast<int>(100 - 1 + 1));
        comms.writeToServer(choice,arguments[0],arguments[1]);
    }

    detector.join();
    return 0;
}
