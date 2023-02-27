#ifndef Detector_h
#define Detector_h

#include <functional>

class Detector{
    public:
        void operator()(int reciver,std::function<void(ServerMessage)> process,int &running);
};

#endif