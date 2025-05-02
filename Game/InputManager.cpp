#include <iostream>
#include "InputManager.h"
#include "UIContainer.h"
#include <vector>

std::vector<std::unique_ptr<Command>> InputManager::handleInput(sf::RenderWindow& window)
{
    std::vector<std::unique_ptr<Command>> commands;
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
            if (uiContainer_) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    uiContainer_->focusNext();
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                    uiContainer_->focusPrevious();
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                    uiContainer_->activateFocused();
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                commands.emplace_back(std::make_unique<DashCommand>(inputDirectionOfPlayer));
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button== sf::Mouse::Button::Left)
            {
                //Placeholder for left mouse button handling
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            if (uiContainer_) {
                sf::Vector2f mousePos(
                    static_cast<float>(mouseMoved->position.x),
                    static_cast<float>(mouseMoved->position.y)
                );
                uiContainer_->focusByMouse(mousePos);
            }
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
        for (const auto& callback : mousePressCbs_)
        {
            callback(*event);
        }
    }
    if(inputDirectionOfPlayer.x != 0 || inputDirectionOfPlayer.y != 0) {
        commands.emplace_back(std::make_unique<MoveCommand>(inputDirectionOfPlayer));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
            commands.emplace_back(std::make_unique<AttackCommand>(inputDirectionOfPlayer));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        commands.emplace_back(std::make_unique<AttackCommand>(sf::Vector2f(1, 0)));
    }
    //return nullptr;

    return commands;
}

void InputManager::registerMousePressCallback(MousePressCallback cb) {
    mousePressCbs_.push_back(std::move(cb));
}