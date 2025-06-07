#include <iostream>
#include <algorithm>
#include "Game/UI/UIManager.h"
#include "Game/UI/UIContainer.h"


void UIManager::addToLayer(UILayer layer, std::shared_ptr<UIContainer> container) 
{
    uiLayers[layer].push_back(container);
}

void UIManager::removeFromLayer(UILayer layer, std::shared_ptr<UIContainer> container) 
{
    auto& vec = uiLayers[layer];
    vec.erase(std::remove(vec.begin(), vec.end(), container), vec.end());
}

void UIManager::drawAll(sf::RenderTarget& target) 
{
    for (auto& [layer, vec] : uiLayers) {
        for (auto& c : vec)
            c->draw(target, sf::RenderStates::Default);
    }
}

void UIManager::updateAll(float deltaTime) 
{
    for (auto& [layer, vec] : uiLayers) {
        for (auto& c : vec)
            c->update(deltaTime);
    }
}