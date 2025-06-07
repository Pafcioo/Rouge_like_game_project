#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "MapManager.h"
#include "Game/UI/UIManager.h"

MapManager::MapManager()
{
    try {
        loadMaps("Assets/mapData.csv");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void MapManager::addMap(const MapData& mapData) {
    mapDataMap[mapData.labelOfMap] = mapData;

    // Create a shared pointer for the GameMap and store it in the map
    gameMaps[mapData.labelOfMap] = std::make_shared<GameMap>(
        mapData.pathToMap, sf::Vector2f(0, 0), mapData.sizeOfGameplayMap
    );
}

void MapManager::removeMap(const std::string& labelOfMap) {
    mapDataMap.erase(labelOfMap);
    gameMaps.erase(labelOfMap);

    // Reset current map label if necessary
    if (currentMapLabel == labelOfMap) {
        currentMapLabel = "";
    }
}

const GameMap& MapManager::getCurrentMap() const {
    if (currentMapLabel.empty()) {
        throw std::runtime_error("No map is currently set");
    }
    return *gameMaps.at(currentMapLabel); // Dereference the shared pointer
}

const std::string& MapManager::getCurrentMapLabel() const {
    return currentMapLabel;
}

void MapManager::loadMaps(const std::string& pathToMaps) {
    std::ifstream file(pathToMaps);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open map file: " + pathToMaps);
    }

    std::string line;
    bool isHeader = true;

    // Regular expression to match sizes in the format [xXy] (e.g., [200x150])
    std::regex sizeRegex(R"(\[([0-9]+(?:\.[0-9]*)?)x([0-9]+(?:\.[0-9]*)?)\])");

    while (std::getline(file, line)) {
        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        std::istringstream lineStream(line);
        std::string labelOfMap, pathToMap, sizeOfPreviewMapStr, sizeOfGameplayMapStr;

        // Parse the CSV line
        std::getline(lineStream, labelOfMap, ',');
        std::getline(lineStream, pathToMap, ',');
        std::getline(lineStream, sizeOfPreviewMapStr, ',');
        std::getline(lineStream, sizeOfGameplayMapStr, ',');

        // Debugging output
        std::cout << "Parsing line: " << line << std::endl;

        // Parse sizeOfPreviewMap using regex
        sf::Vector2f sizeOfPreviewMap;
        std::smatch match;
        if (std::regex_match(sizeOfPreviewMapStr, match, sizeRegex)) {
            sizeOfPreviewMap.x = std::stof(match[1].str());
            sizeOfPreviewMap.y = std::stof(match[2].str());
        } else {
            std::cerr << "Invalid sizeOfPreviewMap format: " << sizeOfPreviewMapStr << std::endl;
            continue;
        }

        // Parse sizeOfGameplayMap using regex
        sf::Vector2f sizeOfGameplayMap;
        if (std::regex_match(sizeOfGameplayMapStr, match, sizeRegex)) {
            sizeOfGameplayMap.x = std::stof(match[1].str());
            sizeOfGameplayMap.y = std::stof(match[2].str());
        } else {
            std::cerr << "Invalid sizeOfGameplayMap format: " << sizeOfGameplayMapStr << std::endl;
            continue;
        }

        // Debugging output
        std::cout << "Parsed sizes: Preview(" << sizeOfPreviewMap.x << ", " << sizeOfPreviewMap.y
                  << "), Gameplay(" << sizeOfGameplayMap.x << ", " << sizeOfGameplayMap.y << ")" << std::endl;

        // Create MapData
        MapData map;
        map.labelOfMap = labelOfMap;
        map.pathToMap = pathToMap;
        map.sizeOfPreviewMap = sizeOfPreviewMap;
        map.sizeOfGameplayMap = sizeOfGameplayMap;

        std::cout << "Loading map: " << map.labelOfMap << std::endl;

        // Add the map
        addMap(map);
    }
}

void MapManager::setMap(const std::string& labelOfMap) {
    if (gameMaps.find(labelOfMap) == gameMaps.end()) {
        throw std::runtime_error("Map not found: " + labelOfMap);
    }
    currentMapLabel = labelOfMap;
    std::cout << "Current map set to: " << currentMapLabel << std::endl;
}

void MapManager::subscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->subscribe<MapChoiceEvent>([this](const MapChoiceEvent& mapEvent) {
        setMap(mapEvent.mapLabel);
    });
}

void MapManager::drawMap(sf::RenderTarget& target) const {
    target.draw(getCurrentMap());
}