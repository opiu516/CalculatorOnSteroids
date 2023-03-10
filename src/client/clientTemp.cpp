#include "coreLogic/commsProtocol.h"
#include "coreLogic/Detector.h"
#include "coreLogic/Writer.h"
#include "client/ClientServerCommunicator.h"
#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <queue>

class ClientUI{
    public:
        ClientUI(ClientServerCommunicator& comms){
            while(true){
                int choice;
                std::cout<<"1 - preform opperation \n2 - close \n"<<std::endl;
                std::cin>>choice;
                switch (choice)
                {
                case 1:
                    chooseOperation(comms);
                    break;
                
                case 2: 
                    return;
                    break;
                default:
                    std::cout<<"Bad Inoput"<<std::endl;
                    break;
                }
            }
        }
    private:
        ClientServerCommunicator comms;
        void chooseOperation(ClientServerCommunicator& comms){
            int choice;
            std::cout<<"1 - + \n2 - - \n3 - * \n4 -* /\n5 - concat\n"<<std::endl;
            std::cin>>choice;
            if(choice < 1 || choice > 5){
                std::cout<<"BadStuff"<<std::endl;
            }
            std::cout<<"enter 2 args"<<std::endl;
            double arguments[2];
            std::cin>>arguments[0]>>arguments[1];
            comms.writeToServer(choice,arguments[0],arguments[1]);
        }
};


int main(){
    ClientServerCommunicator comms;
    int running = 1;
    std::thread detector(Detector(),CLIENT_ID,[&comms](ServerMessage message){
        if(comms.IdContained(message.messageId)){
            comms.process(message);
        }
    },std::ref(running));

    std::thread writer(Writer(),SERVER_ID,std::ref(comms.getMessages()),std::ref(running));

    ClientUI ui(comms);
    running = 0;
    writer.join();
    detector.join();
    return 0;
}
