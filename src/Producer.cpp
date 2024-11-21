#include "Producer.h"
#include <vector>
#include <random>

// Constructor initializes the producer's ID, number of products, and bounded buffer
Producer::Producer(int id, int numProducts, int queueSize)
    : producerId(id), numProducts(numProducts), queue(queueSize) {}

Producer::Producer(Producer&& other) noexcept
    : producerId(other.producerId), numProducts(other.numProducts), queue(std::move(other.queue)), thread(std::move(other.thread)) {
    // After move, other's thread is empty (not joinable)
}
Producer::~Producer() {
    if (thread.joinable()) {
        thread.join();  // Ensure the thread is joined
    }
}

Producer& Producer::operator=(Producer&& other) noexcept {
    if (this != &other) {
        if (thread.joinable()) {
            thread.join();  // Ensure the current thread is joined before overwriting
        }
        producerId = other.producerId;
        numProducts = other.numProducts;
        queue = std::move(other.queue);
        thread = std::move(other.thread);
        // other is left in a valid but indeterminate state
    }
    return *this;
}

// Start the producer thread
void Producer::start() {
    thread = std::thread(&Producer::run, this);
}

// Join the producer thread
void Producer::join() {
    thread.join();
}

// Get the producer's bounded buffer
BoundedBuffer& Producer::getQueue() {
    return queue;
}

// Run method for the producer thread
void Producer::run() {
    std::vector<std::string> types = { "SPORTS", "NEWS", "WEATHER" };
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 2);
    int sportscount = 0;
    int newscount = 0;
    int weathercount = 0;

    for (int j = 0; j < numProducts; ++j) {
        std::string msgType = types[distribution(generator)];
        
    

        // Construct the message
        std::string message = "Producer " + std::to_string(producerId) + " " + msgType + " " ;
        
        // Append the count
        if (msgType == "SPORTS") {
            message += std::to_string(sportscount);
        } else if (msgType == "NEWS") {
            message +=  std::to_string(newscount);
        } else if (msgType == "WEATHER") {
            message +=  std::to_string(weathercount);
        }
         // Increment the appropriate counter
        if (msgType == "SPORTS") {
            ++sportscount;
        } else if (msgType == "NEWS") {
            ++newscount;
        } else if (msgType == "WEATHER") {
            ++weathercount;
        }

        // Insert the message into the queue
        queue.insert(message);
    }
    queue.insert("DONE");
}
