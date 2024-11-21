#include "CoEditor.h"
#include <thread>
#include <chrono>

CoEditor::CoEditor(UnboundedBuffer& inputBuffer, BoundedBuffer& sharedBuffer)
    : inputBuffer(inputBuffer), sharedBuffer(sharedBuffer) {}

void CoEditor::start() {
    thread = std::thread(&CoEditor::run, this);
}
CoEditor::~CoEditor() {
    if (thread.joinable()) {
        thread.join();
    }
}

void CoEditor::join() {
    thread.join();
}

void CoEditor::run() {
    while (true) {
        std::string message = inputBuffer.remove();
        if (message == "DONE") {
            sharedBuffer.insert(message);
            break;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate editing
            sharedBuffer.insert(message);
        }
    }
}
