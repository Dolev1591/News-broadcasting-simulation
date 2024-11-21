#include "Dispatcher.h"

Dispatcher::Dispatcher(int numProducers)
    : numProducers(numProducers), doneCount(0) {}

void Dispatcher::addProducerQueue(BoundedBuffer* queue) {
    producerQueues.push_back(queue);
}

void Dispatcher::start() {
    thread = std::thread(&Dispatcher::run, this);
}
Dispatcher::~Dispatcher() {
    if (thread.joinable()) {
        thread.join();
    }
}

void Dispatcher::join() {
    thread.join();
}

UnboundedBuffer& Dispatcher::getSQueue() {
    return sQueue;
}

UnboundedBuffer& Dispatcher::getNQueue() {
    return nQueue;
}

UnboundedBuffer& Dispatcher::getWQueue() {
    return wQueue;
}

void Dispatcher::run() {
    while (doneCount < numProducers) {
        for (auto& producerQueue : producerQueues) {
            if (!producerQueue->isEmpty()) {
                std::string message = producerQueue->remove();
                if (message == "DONE") {
                    doneCount++;
                } else {
                    sortMessage(message);
                }
            }
        }
    }
    sQueue.insert("DONE");
    nQueue.insert("DONE");
    wQueue.insert("DONE");
}

void Dispatcher::sortMessage(const std::string& message) {
    if (message.find("SPORTS") != std::string::npos) {
        sQueue.insert(message);
    } else if (message.find("NEWS") != std::string::npos) {
        nQueue.insert(message);
    } else if (message.find("WEATHER") != std::string::npos) {
        wQueue.insert(message);
    }
}


