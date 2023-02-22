#include"../coreLogic/commsProtocol.cpp"
#include"../coreLogic/Detector.cpp"
#include"../coreLogic/Writer.cpp"
#include "ClientServerCommunicator.cpp"
#include <iostream>
#include "spdlog/spdlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <queue>

class ClientUI{
    public:
        ClientUI(ClientServerCommunicator& comms){
            while(true){
                int choice;
                std::cout<<"1 - preform opperation \n2 - close"<<std::endl;
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
            std::cout<<"1 - + \n2 - - \n3 - * \n4 -* /"<<std::endl;
            std::cin>>choice;
            if(choice < 1 || choice > 4){
                std::cout<<"BadStuff"<<std::endl;
            }
            std::cout<<"enter 2 args"<<std::endl;
            int arguments[2];
            std::cin>>arguments[0]>>arguments[1];
            comms.writeToServer(choice,arguments[0],arguments[1]);
        }
};


int main(){
    ClientServerCommunicator comms;
    std::thread detector(Detector(),0,[&comms](ServerMessage message){
        if(comms.IdContained(message.messageId)){
            comms.process(message);
        }
    });

    std::thread writer(Writer(),1,std::ref(comms.getMessages()));

    ClientUI ui(comms);
    return 0;
}
