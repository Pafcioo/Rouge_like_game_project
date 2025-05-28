#include <iostream>
#include "math.h"
#include "UIManager.h"
#include "GameManager.h"

void UIManager::addLayer(UILayer uiLayer, std::shared_ptr<UIContainer> container)
{
    uiLayers[uiLayer].push_back(container);
}

void UIManager::removeLayer(UILayer uiLayer)
{
    uiLayers.erase(uiLayer);
}

void UIManager::draw(sf::RenderTarget& target)
{
    for (auto& [layer, uiList] : uiLayers) {
        for (auto& ui : uiList) {
            ui->draw(target,sf::RenderStates::Default);
        }
    }
}