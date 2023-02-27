#ifndef ProtectedQueue_h
#define ProtectedQueue_h

#include<queue>
#include<mutex>

template<typename Type>
class ProtectedQueue{
    public:
        void push(Type item){
            std::lock_guard<std::mutex> lock(queueMutex);
            itemQueue.push(item);
        }
        void pop(){
            std::lock_guard<std::mutex> lock(queueMutex);
            itemQueue.pop();
        }
        Type front(){
            std::lock_guard<std::mutex> lock(queueMutex);
            return itemQueue.front();
        }
        bool empty(){
            std::lock_guard<std::mutex> lock(queueMutex);
            return itemQueue.empty();
        }

    private:
        std::queue<Type> itemQueue;
        std::mutex queueMutex;

};

#endif