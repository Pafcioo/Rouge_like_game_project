#include "GameManager.h"
#include <iostream>


GameManager::GameManager() : font("Assets/Roboto_Condensed-Black.ttf")
{
    auto button = std::make_unique<Button>(
        inputManager,
        sf::Vector2f(100.f, 100.f),
        font,
        sf::Vector2f(200.f, 50.f),
        sf::Color::Green,
        "Start",
        24
    );
    button->setCallback([]() {
        std::cout << "Button clicked!" << std::endl;
        // Add your button click handling logic here
    });
    uiContainer.addElement(std::move(button));
}


void GameManager::Play()
{
    // Create a window
    gameWindow.create(sf::VideoMode::getFullscreenModes() [5], "SFML Game");
    gameWindow.setFramerateLimit(60);

    // Main loop
    while (gameWindow.isOpen())
    {
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        if(deltaTime > 1/60.f) deltaTime = 1.f / 60.f; 
        gameWindow.clear();
        if(inputManager.handleInput(gameWindow)!=nullptr){inputManager.handleInput(gameWindow)->executeCommand();}
        
        uiContainer.drawAll(gameWindow, sf::RenderStates::Default);
        gameWindow.display();
    }
}