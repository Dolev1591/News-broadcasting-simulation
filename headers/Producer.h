#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <thread>
#include <vector>

class Producer {
public:
    Producer(int id, int numProducts, int queueSize);
    Producer(Producer&& other) noexcept;  // Move constructor
    Producer& operator=(Producer&& other) noexcept;  // Move assignment operator
    ~Producer();

    void start();
    void join();
    BoundedBuffer& getQueue();

private:
    void run();

    int producerId;
    int numProducts;
    BoundedBuffer queue;
    std::thread thread;
};

#endif // PRODUCER_H
