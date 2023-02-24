#include"../coreLogic/commsProtocol.cpp"
#include"../coreLogic/Detector.cpp"
#include"../coreLogic/Writer.cpp"
#include "ClientServerCommunicator.cpp"
#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <queue>
#include <mutex>

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
    std::thread detector(Detector(),0,[&comms](ServerMessage message){
        if(comms.IdContained(message.messageId)){
            comms.process(message);
            comms.readMessage();
        }
    },std::ref(running));

    std::thread writer(Writer(),1,std::ref(comms.getMessages()),std::ref(comms.getWritingCueueMutex()),std::ref(running));

    ClientUI ui(comms);
    return 0;
}
