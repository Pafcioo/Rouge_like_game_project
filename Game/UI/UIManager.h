#pragma once
#include <SFML/Graphics.hpp>
#include "UIContainer.h"
#include <unordered_map>
#include <memory>
#include <map>

enum class UILayer
{
    Background = 0,
    State,
    Overlay,
    Debug
};

class UIManager {
public:
    UIManager() = default;
    ~UIManager() = default;
    // Method for adding a UI to unordered map of UIs
    void addToLayer(UILayer layer, std::shared_ptr<UIContainer> container);
    void removeFromLayer(UILayer layer, std::shared_ptr<UIContainer> container);
    // Draw methods for UIs
    void drawAll(sf::RenderTarget& target);
    void updateAll(float deltaTime);
private:
    std::map<UILayer, std::vector<std::shared_ptr<UIContainer>>> uiLayers;
};
