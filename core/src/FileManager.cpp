#include "../inc/FileManager.h"
#include "../inc/GameplayInfoSource.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>

FileManager::FileManager(std::string path): path(std::move(path)) {}

std::unordered_map<std::string, std::any> FileManager::readFile() {
    std::unordered_map<std::string, std::any> info;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        // Initialize with default values if file cannot be opened
        info["EnemiesKilled"] = 0;
        info["Deaths"] = 0;
        return info;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string element;
        std::vector<std::string> elements;
        while (std::getline(ss, element, ' ')) {
            elements.push_back(element);
        }
        info[elements[0]] = stoi(elements[1]);
    }
    file.close();
    return info;
}

void FileManager::writeFile(std::shared_ptr<GameplayInfoSource> infoSource) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    try {
        file << "EnemiesKilled " << infoSource->getInfo<int>("EnemiesKilled") << std::endl;
        file << "Deaths " << infoSource->getInfo<int>("Deaths");
    } catch (const std::runtime_error& e) {
        std::cout << "Error writing file: " << e.what() << std::endl;
    }
    file.close();
}