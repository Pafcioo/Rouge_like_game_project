#include <iostream>
#include <vector>
#include "../inc/InputManager.h"
#include "../inc/Event.h"
#include "../inc/GameState.h"

// Initialize input manager and subscribe to quit events
InputManager::InputManager(std::shared_ptr<EventBus> eventBus, sf::RenderWindow& gameWindow)
    : eventBus(eventBus), window(gameWindow)
{
    // Close window on quit event
    eventBus->subscribe<QuitGameEvent>([this](const QuitGameEvent& quitEvent) {
        window.close();
    });
}

// Process all input and publish events
void InputManager::handleInput(float deltaTime)
{   
    // Movement input (WASD)
    sf::Vector2f inputDirection(0,0);
    sf::Vector2f shootDirection(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            inputDirection.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            inputDirection.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            inputDirection.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            inputDirection.x++;
    // Publish movement event if moving
    if(inputDirection != sf::Vector2f(0,0)){
        eventBus->publish<MoveEvent>({inputDirection, deltaTime});
    }
    
    // Shooting input (Arrow keys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            shootDirection.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            shootDirection.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            shootDirection.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            shootDirection.x++;
    // Publish attack event if shooting
    if (shootDirection != sf::Vector2f(0, 0)) {
        eventBus->publish<AttackEvent>({shootDirection});
    }
    
    // Handle window events
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }
        // Mouse movement for UI hover
        else if( const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            eventBus->publish<sf::Event::MouseMoved>(*mouseMoved);
        }
        // Mouse clicks for UI interaction
        else if( const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(mouseClicked->button == sf::Mouse::Button::Left)
                eventBus->publish<sf::Event::MouseButtonPressed>(*mouseClicked);
        }
        // Key press events
        else if( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            // UI navigation keys
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up || keyPressed->scancode == sf::Keyboard::Scancode::Down || keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                eventBus->publish<sf::Event::KeyPressed>(*keyPressed);
            }
            // Dash ability
            if(keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                eventBus->publish<DashEvent>({inputDirection});
            }
            // Use ability
            if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                eventBus->publish<useAbilityEvent>({});
            }
            // Use item
            if (keyPressed->scancode == sf::Keyboard::Scan::Num1) {
                eventBus->publish<useItemEvent>({});
            }
        }
    }
}