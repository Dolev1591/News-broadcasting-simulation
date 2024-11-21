#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager(BoundedBuffer& buffer)
    : buffer(buffer) {}

void ScreenManager::start() {
    thread = std::thread(&ScreenManager::run, this);
}

void ScreenManager::join() {
    thread.join();
}
ScreenManager::~ScreenManager() {
    if (thread.joinable()) {
        thread.join();
    }
}

void ScreenManager::run() {
    int doneCount = 0;
    while (doneCount < 3) {
        std::string message = buffer.remove();
        if (message == "DONE") {
            doneCount++;
        } else if (!message.empty()) { // Check for empty lines
            std::cout << message << std::endl;
        }
    }
    std::cout << "DONE" << std::endl;
}

