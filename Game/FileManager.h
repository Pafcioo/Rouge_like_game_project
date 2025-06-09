#pragma once
#include <any>
#include <string>
#include <fstream>
#include <unordered_map>

class FileManager {
private:
    std::string path;
public:
    FileManager(std::string path);
    ~FileManager() = default;
    std::unordered_map<std::string, std::any> readFile();
    void writeFile(std::unordered_map<std::string, std::any> info);
};
