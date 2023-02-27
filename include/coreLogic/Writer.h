#ifndef Writer_h
#define Writer_h

#include<functional>
#include "coreLogic/ProtectedQueue.h"

class Writer{
    public:
        void operator()(int reciver,ProtectedQueue<ServerMessage> &messages, int &running);
};

#endif