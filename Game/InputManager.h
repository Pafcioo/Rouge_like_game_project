#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class EventBus;

class InputManager
{
public:
    InputManager() = default;
    ~InputManager() = default;
    void handleInput(float deltaTime, EventBus& eventBus, sf::RenderWindow& window);
};