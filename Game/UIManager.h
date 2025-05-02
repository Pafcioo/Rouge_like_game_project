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
    sf::RectangleShape backgroundShape_;
    sf::Color backgroundColor_ = sf::Color(0, 0, 0, 150); // Semi-transparent black
public:
    UIManager(){
        backgroundShape_.setFillColor(backgroundColor_);
        backgroundShape_.setSize(sf::Vector2f(1280.f, 720.f)); // Set the size to match the window size
    };
    ~UIManager() = default;

    void addUIContainer(GameState state, std::shared_ptr<UIContainer> container);
    void drawUI(sf::RenderTarget& target, GameState state);
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states)
    {
        target.draw(backgroundShape_, states);
    };
    void initAllUI(InputManager& inputManager, sf::Font& font,
        std::function<void(GameState)> changeStateCallback,
        std::function<GameState()> getStateCallback);
    std::shared_ptr<UIContainer> getUIContainer(GameState state);
    std::shared_ptr<UIContainer> createUI(GameState state, InputManager& inputManager, sf::Font& font,
        std::function<void(GameState)> changeStateCallback,
        std::function<GameState()> getStateCallback);
};
