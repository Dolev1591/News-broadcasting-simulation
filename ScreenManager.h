#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <thread>

class ScreenManager {
public:
    ScreenManager(BoundedBuffer& buffer);
    ~ScreenManager();
    void start();
    void join();

private:
    BoundedBuffer& buffer;
    std::thread thread;

    void run();
};
#endif