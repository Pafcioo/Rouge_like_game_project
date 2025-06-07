#include <iostream>
#include "InputManager.h"
#include "Event.h"
#include <vector>
#include <cmath>

// Handle input method for publishing events to event bus
void InputManager::handleInput(float deltaTime, std::shared_ptr<EventBus> eventBus, sf::RenderWindow& window)
{   
    // Section responsible for movement
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
        //std::cout << "Move event published" << std::endl;
        eventBus->publish<MoveEvent>({inputDirection, deltaTime});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        eventBus->publish<AttackEvent>({inputDirection});
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if( const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            eventBus->publish<sf::Event::MouseMoved>(*mouseMoved); // Hover effect for buttons...
        }
        else if( const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(mouseClicked->button == sf::Mouse::Button::Left)
                eventBus->publish<sf::Event::MouseButtonPressed>(*mouseClicked); // Mouse clicking
        }
        else if( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up || keyPressed->scancode == sf::Keyboard::Scancode::Down || keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                eventBus->publish<sf::Event::KeyPressed>(*keyPressed); // Navigating UI with arrows
            }
            // Publishing events other tat KeyPressed
            /*if(keyPressed->scancode == sf::Keyboard::Scancode::Q)
                eventBus->publish<AttackEvent>({inputDirection}); // Attacking*/
            if(keyPressed->scancode == sf::Keyboard::Scancode::Space)
                eventBus->publish<DashEvent>({inputDirection}); // Dashing
            if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                eventBus->publish<useAbilityEvent>({});
            }
        }
    }
}