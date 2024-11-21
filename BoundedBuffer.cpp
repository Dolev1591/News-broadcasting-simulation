#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int mysize)
    : mysize(mysize), count(0) {
    sem_init(&items, 0, 0);
    sem_init(&spaces, 0, mysize);
}
BoundedBuffer::BoundedBuffer(BoundedBuffer&& other) noexcept
    : mysize(other.mysize), count(other.count), buffer(std::move(other.buffer)),
      mtx(), items(), spaces() {
    // Transfer semaphore state, this requires platform-specific solutions or might be tricky
    items = std::move(other.items);
    spaces = std::move(other.spaces);
    // Reset the other's semaphores, if necessary (platform-specific)
    sem_init(&other.items, 0, 0);  // Reinitialize to a valid state if needed
    sem_init(&other.spaces, 0, 0);  // Reinitialize to a valid state if needed
}

// Move assignment operator
BoundedBuffer& BoundedBuffer::operator=(BoundedBuffer&& other) noexcept {
    if (this != &other) {
        mysize = other.mysize;
        count = other.count;
        buffer = std::move(other.buffer);

        // Properly destroy or reset current semaphores before moving
        sem_destroy(&items);
        sem_destroy(&spaces);

        // Move semaphores
        items = std::move(other.items);
        spaces = std::move(other.spaces);

        // Reinitialize the other's semaphores
        sem_init(&other.items, 0, 0);
        sem_init(&other.spaces, 0, 0);
    }
    return *this;
}

// Destructor
BoundedBuffer::~BoundedBuffer() {
    sem_destroy(&items);
    sem_destroy(&spaces);
}

void BoundedBuffer::insert(const std::string &s) {
    sem_wait(&spaces);
    std::unique_lock<std::mutex> lock(mtx);
    buffer.push(s);
    ++count;
    lock.unlock();
    sem_post(&items);
}

std::string BoundedBuffer::remove() {
    sem_wait(&items);
    std::unique_lock<std::mutex> lock(mtx);
    std::string item = buffer.front();
    buffer.pop();
    --count;
    lock.unlock();
    sem_post(&spaces);
    return item;
}

size_t BoundedBuffer::size() {
    std::unique_lock<std::mutex> lock(mtx);
    return static_cast<size_t>(buffer.size());
}

bool BoundedBuffer::isEmpty() {
    std::unique_lock<std::mutex> lock(mtx);
    return buffer.empty();
}
