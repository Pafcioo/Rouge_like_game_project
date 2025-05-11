#include "GameManager.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

GameManager::GameManager() : uiManager(*this),font("Assets/Roboto_Condensed-Black.ttf"),
    gameMap("Assets/Map.png", {0,0}, {1280*8, 720*8})
{
    entityManager.subscribeToEvents(eventBus);
    uiManager.initAllUI(eventBus, font);
    uiManager.updateActiveUI(currentGameState);
    currentGameState = GameState::MainMenu;
    defaultView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    gameplayView = sf::View(sf::FloatRect({0,0},{1280, 720}));
}

void GameManager::changeGameplayViewBasedOnPlayer()
    {
        Entity* player = entityManager.getPlayer();
        if (player)
        {
            sf::Vector2f playerPosition = player->getPosition();
            gameplayView.setCenter(playerPosition);
        }
    };

void GameManager::changeGameState(GameState newState) {
    currentGameState = newState;
    uiManager.updateActiveUI(currentGameState);
    entityManager.updateEntityManager(newState);
}

UIManager GameManager::getUIManager()
{
    return uiManager;
}

GameState GameManager::getGameState() const {
    return currentGameState; 
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
        // In this section the gameplayerView changes in specific order so 
        // background is first, then the player and at the end is UI that is static
        // relativly to player, so the player is always in the center of view
        changeGameplayViewBasedOnPlayer();
        gameWindow.setView(gameplayView);
        gameMap.draw(gameWindow);
        entityManager.updateEntities(deltaTime,eventBus);
        entityManager.drawEntities(gameWindow);
        gameWindow.setView(defaultView);
        uiManager.drawUI(gameWindow, currentGameState); // UI elements are drwan based on the current state of the game
        //
        gameWindow.display();
    }
}