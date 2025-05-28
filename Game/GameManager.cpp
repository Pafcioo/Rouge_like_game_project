#include "GameManager.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

GameManager::GameManager() : uiManager(*this),font("Assets/Roboto_Condensed-Black.ttf")
{
    // Bus for events in game
    eventBus = std::make_shared<EventBus>();
    // Manager for all UIs
    uiManager.initAllUI(eventBus, font);
    // View set up
    defaultView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    gameplayView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    // Source for all game info like level, hp, position of player...
    gameplayInfoSource = std::make_shared<GameplayInfoSource>();
    // Managers for entities like player and enemy
    entityManager.setGameplayInfo(gameplayInfoSource);
    entityManager.subscribeToEvents(eventBus);
    enemyManager = std::make_shared<EnemyManager>();
    // Spawner set up
    spawnManager = std::make_unique<SpawnManager>();
    spawnManager->setUpStrategies(gameplayInfoSource,enemyManager);
}

void GameManager::changeGameplayViewBasedOnPlayer() {
    Entity* player = entityManager.getPlayer();
    if (!player) return;

    sf::Vector2f playerPosition = player->getPosition();

    if (!mapManager.getCurrentMapLabel().empty()) {
        sf::Vector2f halfMapSize = mapManager.getCurrentMap().getSize() / 2.f;
        sf::Vector2f viewSize = gameplayView.getSize();
        sf::Vector2f halfViewSize = viewSize / 2.f;

        float clampedX = playerPosition.x;
        float clampedY = playerPosition.y;

        // Lewa do prawa: od -halfMapSize.x + halfViewSize.x do +halfMapSize.x - halfViewSize.x
        clampedX = std::max(-halfMapSize.x + halfViewSize.x,
                            std::min(clampedX, halfMapSize.x - halfViewSize.x));

        // Góra do dołu: od -halfMapSize.y + halfViewSize.y do +halfMapSize.y - halfViewSize.y
        clampedY = std::max(-halfMapSize.y + halfViewSize.y,
                            std::min(clampedY, halfMapSize.y - halfViewSize.y));

        gameplayView.setCenter({clampedX, clampedY});


        gameplayView.setCenter({clampedX, clampedY});
    } else {
        gameplayView.setCenter(playerPosition);
    }
}

UIManager GameManager::getUIManager()
{
    return uiManager;
}

MapManager& GameManager::getMapManager() {
    return mapManager;
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
        spawnManager->update(deltaTime);
        // In this section the gameplayerView changes in specific order so 
        // background is first, then the player and at the end is UI that is static
        // relativly to player, so the player is always in the center of view
        changeGameplayViewBasedOnPlayer();
        gameWindow.setView(gameplayView);
        mapManager.drawMap(gameWindow, currentGameState);//STATE
        entityManager.updateEntities(deltaTime);
        enemyManager->update(deltaTime);
        enemyManager->drawEnemies(gameWindow);
        entityManager.drawEntities(gameWindow);
        gameWindow.setView(defaultView);
        uiManager.updateActiveUI(currentGameState);//STATE
        uiManager.drawUI(gameWindow, currentGameState); // UI elements are drwan based on the current state of the game, STATE
        gameWindow.display();
    }
}