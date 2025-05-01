#pragma once
#include <SFML/Graphics.hpp>
#include "Command.h"
#include <functional>

class UIContainer;

class InputManager
{
public:
    using MousePressCallback = std::function<void(const sf::Event&)>;
    InputManager() = default;
    ~InputManager() = default;
    std::unique_ptr<Command> handleInput(sf::RenderWindow& window);
    void registerMousePressCallback(MousePressCallback cb);
    void setUIContainer(UIContainer* container) { uiContainer_ = container; }
private:
    std::vector<MousePressCallback> mousePressCbs_;
    UIContainer* uiContainer_ = nullptr;
};