#include "coreLogic/commsProtocol.h"
#include "coreLogic/Detector.h"
#include "coreLogic/Writer.h"
#include "client/ClientServerCommunicator.h"
#include "spdlog/spdlog.h"
#include <thread>
#include <unistd.h>
#include <random>



int main(){
    ClientServerCommunicator comms;
    int running = 1;
    std::thread detector(Detector(),CLIENT_ID,[&comms](ServerMessage message){
        if(comms.IdContained(message.messageId)){
            comms.process(message);
            comms.readMessage();
        }
    },std::ref(running));

    std::thread writer(Writer(),SERVER_ID,std::ref(comms.getMessages()),std::ref(comms.getWritingCueueMutex()),std::ref(running));

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
