#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class EventBus;

class InputManager
{
private:
    std::shared_ptr<EventBus> eventBus;
    sf::RenderWindow& window;  // Referencja zamiast kopii
public:
    InputManager(std::shared_ptr<EventBus> eventBus, sf::RenderWindow& gameWindow);
    ~InputManager() = default;
    void handleInput(float deltaTime);
};