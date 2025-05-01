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
    Options,
    GameOver
};



class UIManager
{
private:
    std::unordered_map<GameState, std::shared_ptr<UIContainer>> uiContainers_;
public:
    UIManager() = default;
    ~UIManager() = default;

    void addUIContainer(GameState state, std::shared_ptr<UIContainer> container);
    void drawUI(sf::RenderTarget& target, GameState state);
    void initAllUI(InputManager& inputManager, sf::Font& font,
        std::function<void(GameState)> changeStateCallback,
        std::function<GameState()> getStateCallback);
    UIContainer* getUIContainer(GameState state);
    std::shared_ptr<UIContainer> createUI(GameState state, InputManager& inputManager, sf::Font& font,
        std::function<void(GameState)> changeStateCallback,
        std::function<GameState()> getStateCallback);
};
