#include <iostream>
#include "InputManager.h"
#include "Event.h"
#include <vector>

void InputManager::handleInput(float deltaTime, EventBus& eventBus, sf::RenderWindow& window)
{
    sf::Vector2f inputDirection(0,0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            inputDirection.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            inputDirection.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            inputDirection.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            inputDirection.x++;
    if(inputDirection != sf::Vector2f(0,0)){
        eventBus.publish<MoveEvent>({inputDirection, deltaTime});
    }
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if( const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            eventBus.publish<sf::Event::MouseMoved>(*mouseMoved);
        }
        else if( const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(mouseClicked->button == sf::Mouse::Button::Left)
                eventBus.publish<sf::Event::MouseButtonPressed>(*mouseClicked);
        }
        else if( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up || keyPressed->scancode == sf::Keyboard::Scancode::Down || keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                eventBus.publish<sf::Event::KeyPressed>(*keyPressed);
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::Q)
                eventBus.publish<AttackEvent>({inputDirection});
            if(keyPressed->scancode == sf::Keyboard::Scancode::Space)
                eventBus.publish<DashEvent>({inputDirection});
        }
    }
}