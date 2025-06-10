#include <iostream>
#include <vector>
#include "core/inc/InputManager.h"
#include "core/inc/Event.h"
#include "core/inc/GameState.h"


InputManager::InputManager(std::shared_ptr<EventBus> eventBus, sf::RenderWindow& gameWindow)
    : eventBus(eventBus), window(gameWindow)  // Inicjalizacja przez listę inicjalizacyjną
{
    // Poprawka w subscribe - prawdopodobnie chciałeś QuitGameEvent zamiast MoveEvent
    eventBus->subscribe<QuitGameEvent>([this](const QuitGameEvent& quitEvent) {
        window.close();  // Teraz możesz używać referencji do okna
    });
}

// Handle input method for publishing events to event bus
void InputManager::handleInput(float deltaTime)
{   
    // Section responsible for movement
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
    if(inputDirection != sf::Vector2f(0,0)){
        //std::cout << "Move event published" << std::endl;
        eventBus->publish<MoveEvent>({inputDirection, deltaTime});
    }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            shootDirection.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            shootDirection.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            shootDirection.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            shootDirection.x++;
    if (shootDirection != sf::Vector2f(0, 0)) {
        eventBus->publish<AttackEvent>({shootDirection});
    }
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
            if(keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                eventBus->publish<DashEvent>({inputDirection}); // Dashing
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                eventBus->publish<useAbilityEvent>({});
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num1) {
                eventBus->publish<useItemEvent>({});
            }
        }
    }
}