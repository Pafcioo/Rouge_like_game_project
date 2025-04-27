#include "GameManager.h"
#include <iostream>


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
        inputManager.handleInput(gameWindow)->executeCommand();
        gameWindow.display();
    }
}