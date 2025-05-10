#include "GameManager.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

UIManager GameManager::getUIManager()
{
    return uiManager;
}

void GameManager::changeGameState(GameState newState) {
    currentGameState = newState;
    uiManager.updateActiveUI(currentGameState);
    entityManager.updateEntityManager(newState);
}

GameManager::GameManager() : uiManager(*this),font("Assets/Roboto_Condensed-Black.ttf"),
    gameMap("Assets/Map.png", {0,0}, {1280*8, 720*8})
{
    entityManager.subscribeToEvents(eventBus);
    uiManager.initAllUI(eventBus, font);
    uiManager.updateActiveUI(currentGameState);
}

void GameManager::Play()
{
    // Create a window
    gameWindow.create(sf::VideoMode({1280, 720}), "SFML Game");
    gameWindow.setFramerateLimit(60);
    // Main loop
    while (gameWindow.isOpen())
    {
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        if(deltaTime > 1/60.f) deltaTime = 1.f / 60.f; 
        gameWindow.clear();
        inputManager.handleInput(deltaTime, eventBus, gameWindow);
        changeGameplayViewBasedOnPlayerPosition();
        gameWindow.setView(gameplayView);
        gameMap.draw(gameWindow, sf::RenderStates::Default);
        entityManager.updateEntities(deltaTime,eventBus);
        entityManager.drawEntities(gameWindow);
        gameWindow.setView(defaultView);
        uiManager.drawUI(gameWindow, currentGameState);
        gameWindow.display();
    }
}