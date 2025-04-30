#pragma once
#include <SFML/Graphics.hpp>
#include "UIContainer.h"
#include <unordered_map>
#include <memory>

enum class GameState
{
    MainMenu,
    Playing,
    Paused,
    GameOver
};

class UIManager
{
    private:
        std::unordered_map<GameState, std::shared_ptr<UIContainer>> uiContainers_;
    public:
        UIManager() = default;
        ~UIManager() = default;

        void addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
            uiContainers_[state] = std::move(container);
        }

        void drawUI(sf::RenderTarget& target, GameState state) {
            auto it = uiContainers_.find(state);
            if (it != uiContainers_.end() && it->second) {
                it->second->drawAll(target, sf::RenderStates::Default);
            }
        }

        UIContainer* getUIContainer(GameState state) {
            auto it = uiContainers_.find(state);
            if (it != uiContainers_.end()) {
                return it->second.get();
            }
            return nullptr;
        }
};
