#pragma once
#include <SFML/Graphics.hpp>
#include "UIContainer.h"
#include "Button.h"
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

class InputManager;

class UIManager
{
private:
    std::unordered_map<GameState, std::shared_ptr<UIContainer>> uiContainers_;
public:
    UIManager() = default;
    ~UIManager() = default;

    void addUIContainer(GameState state, std::shared_ptr<UIContainer> container);
    void drawUI(sf::RenderTarget& target, GameState state);
    void initMainMenuUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback, std::function<GameState()> getStateCallback);
    void initOptionsUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback, std::function<GameState()> getStateCallback);
    void initPauseUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback, std::function<GameState()> getStateCallback);
    void initAllUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback, std::function<GameState()> getStateCallback) {
        initMainMenuUI(inputManager, font, changeStateCallback, getStateCallback);
        initOptionsUI(inputManager, font, changeStateCallback, getStateCallback);
        initPauseUI(inputManager, font, changeStateCallback, getStateCallback);
    }
    UIContainer* getUIContainer(GameState state);
};
