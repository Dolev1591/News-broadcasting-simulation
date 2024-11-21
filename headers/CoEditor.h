#ifndef COEDITOR_H
#define COEDITOR_H

#include "UnboundedBuffer.h"
#include "BoundedBuffer.h"
#include <thread>
#include <string>

class CoEditor {
public:
    CoEditor(UnboundedBuffer& inputBuffer, BoundedBuffer& sharedBuffer);
    void start();
    void join();
    ~CoEditor(); // Destructor


private:
    UnboundedBuffer& inputBuffer;
    BoundedBuffer& sharedBuffer;
    std::thread thread;

    void run();
};

#endif // COEDITOR_H
