#pragma once
#include <SFML/Graphics.hpp>
#include "Command.h"

class InputManager
{
public:
    InputManager() = default;
    ~InputManager() = default;

    std::unique_ptr<Command> handleInput(sf::RenderWindow& window);
};