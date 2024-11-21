#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <string>
#include <mutex>
#include <semaphore.h>

class BoundedBuffer {
public:
    BoundedBuffer(int mysize);
    BoundedBuffer(const BoundedBuffer&) = delete;  // No copying allowed
    BoundedBuffer& operator=(const BoundedBuffer&) = delete;  // No copy assignment allowed
    BoundedBuffer(BoundedBuffer&& other) noexcept;  // Move constructor
    BoundedBuffer& operator=(BoundedBuffer&& other) noexcept;  // Move assignment operator
    ~BoundedBuffer();  // Destructor

    void insert(const std::string &s);
    std::string remove();
    size_t size();
    bool isEmpty();

private:
    int mysize;
    int count;
    std::queue<std::string> buffer;
    std::mutex mtx;
    sem_t items;
    sem_t spaces;
};

#endif // BOUNDED_BUFFER_H
