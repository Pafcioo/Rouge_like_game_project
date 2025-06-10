#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <memory>

// Forward declaration
class GameplayInfoSource;

class FileManager {
private:
    std::string path;
public:
    FileManager(std::string path);
    ~FileManager() = default;
    std::unordered_map<std::string, std::any> readFile();
    void writeFile(std::shared_ptr<GameplayInfoSource> infoSource);
};
