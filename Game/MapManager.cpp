#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "json.hpp" // Include the nlohmann/json library
#include "MapManager.h"
#include "UIManager.h"

using json = nlohmann::json;

MapManager::MapManager()
{
    try {
        loadMaps("Assets/mapData.json");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void MapManager::addMap(const MapData& mapData) {
    mapDataMap[mapData.labelOfMap] = mapData;

    // Create a shared pointer for the GameMap and store it in the map
    gameMaps[mapData.labelOfMap] = std::make_shared<GameMap>(
        mapData.pathToMap, sf::Vector2f(640, 360), mapData.sizeOfGameplayMap
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


void MapManager::loadMaps(const std::string& pathToMaps) {
    std::ifstream file(pathToMaps);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open map file: " + pathToMaps);
    }

    json jsonData;
    file >> jsonData;

    for (const auto& mapData : jsonData["maps"]) {
        MapData map;
        map.labelOfMap = mapData["labelOfMap"];
        map.pathToMap = mapData["pathToMap"];
        map.sizeOfPreviewMap = sf::Vector2f(
            mapData["sizeOfPreviewMap"][0],
            mapData["sizeOfPreviewMap"][1]
        );
        map.sizeOfGameplayMap = sf::Vector2f(
            mapData["sizeOfGameplayMap"][0],
            mapData["sizeOfGameplayMap"][1]
        );
        std::cout << "Loading map: " << map.labelOfMap << std::endl;
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

void MapManager::drawMap(sf::RenderWindow& window, GameState currentGameState) const {
    if (currentGameState == GameState::Playing && !currentMapLabel.empty()) {
        window.draw(getCurrentMap());
    }
}