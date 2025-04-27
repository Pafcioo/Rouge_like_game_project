#include "GameManager.h"
#include <iostream>


void GameManager::Play()
{
    // Create a window
    gameWindow.create(sf::VideoMode({800, 600}), "SFML Game");

    // Main loop
    while (gameWindow.isOpen())
    {
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        gameWindow.clear();
        gameWindow.display();
    }
}