#include <iostream>
#include <fstream>
#include <sstream>
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"

struct ProducerConfig {
    int id;
    int numProducts;
    int queueSize;
};

void parseProducerFile(const std::string& filename, std::vector<ProducerConfig>& producers, int& coEditorQueueSize) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            ProducerConfig config;
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> config.id;

            std::getline(file, line);
            config.numProducts = std::stoi(line);

            std::getline(file, line);
            std::size_t pos = line.find('=');
            if (pos != std::string::npos) {
                config.queueSize = std::stoi(line.substr(pos + 1));
            }

            producers.push_back(config);
        }
        else if (line.find("Co-Editor queue size") != std::string::npos) {
            std::size_t pos = line.find('=');
            if (pos != std::string::npos) {
                coEditorQueueSize = std::stoi(line.substr(pos + 1));
            }
        }
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    std::string configFilename = argv[1];
    std::vector<ProducerConfig> producerConfigs;
    int coEditorQueueSize=0;

    parseProducerFile(configFilename, producerConfigs, coEditorQueueSize);

    std::vector<Producer> producers;
    for (const auto& config : producerConfigs) {
        producers.emplace_back(config.id, config.numProducts, config.queueSize);
}

  Dispatcher dispatcher(static_cast<int>(producers.size()));
    for (auto& producer : producers) {
        dispatcher.addProducerQueue(&producer.getQueue());
}   

    for (auto& producer : producers) {
        producer.start();
    }
    dispatcher.start();

    BoundedBuffer sharedBuffer(coEditorQueueSize);
    CoEditor sportsEditor(dispatcher.getSQueue(), sharedBuffer);
    CoEditor newsEditor(dispatcher.getNQueue(), sharedBuffer);
    CoEditor weatherEditor(dispatcher.getWQueue(), sharedBuffer);

    sportsEditor.start();
    newsEditor.start();
    weatherEditor.start();

    for (auto& producer : producers) {
        producer.join();
    }
    dispatcher.join();

    ScreenManager screenManager(sharedBuffer);
    screenManager.start();
    screenManager.join();

    return 0;
}