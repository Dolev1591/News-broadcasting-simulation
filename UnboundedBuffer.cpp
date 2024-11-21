#include "UnboundedBuffer.h"

void UnboundedBuffer::insert(const std::string &s) {
    std::lock_guard<std::mutex> lock(mtx);
    buffer.push(s);
}
UnboundedBuffer::~UnboundedBuffer() {
    // Optional: Log or perform any final cleanup if necessary
}

std::string UnboundedBuffer::remove() {
    std::lock_guard<std::mutex> lock(mtx);
    if (buffer.empty()) return "";
    std::string item = buffer.front();
    buffer.pop();
    return item;
}

bool UnboundedBuffer::isEmpty() {
    std::lock_guard<std::mutex> lock(mtx);
    return buffer.empty();
}
