#ifndef Writer_h
#define Writer_h

#include<functional>
#include<queue>
#include <mutex>

class Writer{
    public:
        void operator()(int reciver,std::queue<ServerMessage> &messages,std::mutex &queueMutex, int &running);
};

#endif