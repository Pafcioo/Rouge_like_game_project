#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "MapManager.h"
#include "Game/UI/UIManager.h"

// Constructor loads maps from CSV file
MapManager::MapManager()
{
   try {
       loadMaps("Assets/mapData.csv");
   } catch (const std::exception& e) {
       std::cerr << "Error: " << e.what() << std::endl;
   }
}

// Add map to both data and game object collections
void MapManager::addMap(const MapData& mapData) {
   mapDataMap[mapData.labelOfMap] = mapData;

   // Create shared pointer for GameMap
   gameMaps[mapData.labelOfMap] = std::make_shared<GameMap>(
       mapData.pathToMap, sf::Vector2f(0, 0), mapData.sizeOfGameplayMap
   );
}

// Remove map from collections and reset current if needed
void MapManager::removeMap(const std::string& labelOfMap) {
   mapDataMap.erase(labelOfMap);
   gameMaps.erase(labelOfMap);

   // Clear current map if it was removed
   if (currentMapLabel == labelOfMap) {
       currentMapLabel = "";
   }
}

// Get current active map, throw if none set
const GameMap& MapManager::getCurrentMap() const {
   if (currentMapLabel.empty()) {
       throw std::runtime_error("No map is currently set");
   }
   return *gameMaps.at(currentMapLabel); // Dereference shared_ptr
}

const std::string& MapManager::getCurrentMapLabel() const {
   return currentMapLabel;
}

// Parse CSV file and load all maps
void MapManager::loadMaps(const std::string& pathToMaps) {
   std::ifstream file(pathToMaps);
   if (!file.is_open()) {
       throw std::runtime_error("Failed to open map file: " + pathToMaps);
   }

   std::string line;
   bool isHeader = true;

   // Regex for [XxY] format (e.g., [200x150])
   std::regex sizeRegex(R"(\[([0-9]+(?:\.[0-9]*)?)x([0-9]+(?:\.[0-9]*)?)\])");

   while (std::getline(file, line)) {
       // Skip header row
       if (isHeader) {
           isHeader = false;
           continue;
       }

       std::istringstream lineStream(line);
       std::string labelOfMap, pathToMap, sizeOfPreviewMapStr, sizeOfGameplayMapStr;

       // Parse CSV columns
       std::getline(lineStream, labelOfMap, ',');
       std::getline(lineStream, pathToMap, ',');
       std::getline(lineStream, sizeOfPreviewMapStr, ',');
       std::getline(lineStream, sizeOfGameplayMapStr, ',');

       // Extract preview map dimensions
       sf::Vector2f sizeOfPreviewMap;
       std::smatch match;
       if (std::regex_match(sizeOfPreviewMapStr, match, sizeRegex)) {
           sizeOfPreviewMap.x = std::stof(match[1].str());
           sizeOfPreviewMap.y = std::stof(match[2].str());
       } else {
           std::cerr << "Invalid sizeOfPreviewMap format: " << sizeOfPreviewMapStr << std::endl;
           continue;
       }

       // Extract gameplay map dimensions
       sf::Vector2f sizeOfGameplayMap;
       if (std::regex_match(sizeOfGameplayMapStr, match, sizeRegex)) {
           sizeOfGameplayMap.x = std::stof(match[1].str());
           sizeOfGameplayMap.y = std::stof(match[2].str());
       } else {
           std::cerr << "Invalid sizeOfGameplayMap format: " << sizeOfGameplayMapStr << std::endl;
           continue;
       }

       // Create and add map data
       MapData map;
       map.labelOfMap = labelOfMap;
       map.pathToMap = pathToMap;
       map.sizeOfPreviewMap = sizeOfPreviewMap;
       map.sizeOfGameplayMap = sizeOfGameplayMap;

       addMap(map);
   }
}

// Set active map by label
void MapManager::setMap(const std::string& labelOfMap) {
   if (gameMaps.find(labelOfMap) == gameMaps.end()) {
       throw std::runtime_error("Map not found: " + labelOfMap);
   }
   currentMapLabel = labelOfMap;
}

// Subscribe to map choice events
void MapManager::subscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
   eventBus->subscribe<MapChoiceEvent>([this](const MapChoiceEvent& mapEvent) {
       setMap(mapEvent.mapLabel);
   });
}

// Render current map to target
void MapManager::drawMap(sf::RenderTarget& target) const {
   target.draw(getCurrentMap());
}