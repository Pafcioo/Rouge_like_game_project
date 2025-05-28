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
    void addLayer(UILayer uiLayer, std::shared_ptr<UIContainer> container);
    void removeLayer(UILayer uiLayer);
    // Draw methods for UIs
    void draw(sf::RenderTarget& target);
private:
    std::map<UILayer, std::vector<std::shared_ptr<UIContainer>>> uiLayers;
};
