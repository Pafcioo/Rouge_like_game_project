#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "Event.h"
#include "GameMap.h"

struct MapData
{
    std::string pathToMap;
    sf::Vector2f sizeOfPreviewMap;
    sf::Vector2f sizeOfGameplayMap;
    std::string labelOfMap;
};

class MapManager
{
private:
    std::unordered_map<std::string, MapData> mapDataMap; // Map label -> MapData
    std::unordered_map<std::string, std::shared_ptr<GameMap>> gameMaps; // Map label -> GameMap (smart pointer)
    std::string currentMapLabel; // Label of the currently active map

public:
    MapManager();
    ~MapManager() = default;

    void addMap(const MapData& mapData);
    void removeMap(const std::string& labelOfMap);
    const GameMap& getCurrentMap() const;
    const std::string& getCurrentMapLabel() const;
    void loadMaps(const std::string& pathToMaps);
    void setMap(const std::string& labelOfMap);
    void subscribeToEvents(std::shared_ptr<EventBus> eventBus);
    void drawMap(sf::RenderTarget& target) const;
};