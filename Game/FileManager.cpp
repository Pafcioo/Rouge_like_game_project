#include "FileManager.h"

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

FileManager::FileManager(std::string path): path(std::move(path)) {}

std::unordered_map<std::string, std::any> FileManager::readFile() {
    std::unordered_map<std::string, std::any> info;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
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

void FileManager::writeFile(std::unordered_map<std::string, std::any> info) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    file << "EnemiesKilled " << std::any_cast<int>(info["EnemiesKilled"]) << std::endl;
    file << "Deaths " << std::any_cast<int>(info["Deaths"]);
    file.close();
    std::cout << "File written" << std::endl;
}