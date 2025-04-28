#include <iostream>
#include "InputManager.h"

std::unique_ptr<Command> InputManager::handleInput(sf::RenderWindow& window)
{
    sf::Vector2f inputDirectionOfPlayer(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) inputDirectionOfPlayer.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) inputDirectionOfPlayer.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) inputDirectionOfPlayer.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) inputDirectionOfPlayer.x += 1;
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                return std::make_unique<DashCommand>(inputDirectionOfPlayer);
            
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button== sf::Mouse::Button::Left)
            {
                for (const auto& callback : mousePressCbs_)
                {
                    callback(*event);
                }
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            // Placeholder for mouse movement handling
        }
        else
        if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            switch (mouseWheelScrolled->wheel)
            {
                // Placeholder for mouse wheel scroll handling
            }
        }
    }
    return std::make_unique<MoveCommand>(inputDirectionOfPlayer);    
}

void InputManager::registerMousePressCallback(MousePressCallback cb) {
    mousePressCbs_.push_back(std::move(cb));
}