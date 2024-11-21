#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"
#include <thread>
#include <vector>

class Dispatcher {
public:
    Dispatcher(int numProducers);
    void addProducerQueue(BoundedBuffer* queue);
     ~Dispatcher();
    void start();
    void join();
    UnboundedBuffer& getSQueue();
    UnboundedBuffer& getNQueue();
    UnboundedBuffer& getWQueue();

private:
    void run();
    void sortMessage(const std::string& message);

    int numProducers;
    int doneCount;
    UnboundedBuffer sQueue; // SPORTS queue
    UnboundedBuffer nQueue; // NEWS queue
    UnboundedBuffer wQueue; // WEATHER queue
    std::vector<BoundedBuffer*> producerQueues; // Vector of producer queues
    std::thread thread;
};

#endif // DISPATCHER_H
