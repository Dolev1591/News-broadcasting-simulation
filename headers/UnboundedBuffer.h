#ifndef UNBOUNDEDBUFFER_H
#define UNBOUNDEDBUFFER_H

#include <queue>
#include <string>
#include <mutex>

class UnboundedBuffer {
public:
    void insert(const std::string &s);
    std::string remove();
    bool isEmpty();
    ~UnboundedBuffer(); // Destructor


private:
    std::queue<std::string> buffer;
    std::mutex mtx;
};

#endif // UNBOUNDED_BUFFER_H
