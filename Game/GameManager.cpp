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
    currentGameState = GameState::MainMenu;
    // View set up
    defaultView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    gameplayView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    // Source for all game info like level, hp, position of player...
    gameplayInfoSource = std::make_shared<GameplayInfoSource>();
    // Managers for entities like player and enemy
    playerManager.setGameplayInfo(gameplayInfoSource);
    playerManager.subscribeToEvents(eventBus);
    enemyManager = std::make_shared<EnemyManager>();
    // Spawner set up
    spawnManager = std::make_unique<SpawnManager>();
    spawnManager->setUpStrategies(gameplayInfoSource,enemyManager);
}

void GameManager::changeGameplayViewBasedOnPlayer() {
    Entity* player = playerManager.getPlayer();
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


void GameManager::changeGameState(GameState newState) {
    currentGameState = newState;
    uiManager.updateActiveUI(currentGameState);
    playerManager.updateEntityManager(newState);
}

UIManager GameManager::getUIManager()
{
    return uiManager;
}

GameState GameManager::getGameState() const {
    return currentGameState; 
}

MapManager& GameManager::getMapManager() {
    return mapManager;
}

PlayerManager& GameManager::getPlayerManager() {
    return playerManager;
}

ProjectileManager& GameManager::getProjectileManager() {
    return projectileManager;
}

std::shared_ptr<EnemyManager> GameManager::getEnemyManager() {
    return enemyManager;
}

void GameManager::update(float deltaTime) {
    playerManager.updateEntities(deltaTime);
    projectileManager.updateProjectiles(deltaTime);
    enemyManager->update(deltaTime);
}

void GameManager::draw() {
    playerManager.drawEntities(gameWindow);
    projectileManager.drawProjectiles(gameWindow);
    enemyManager->drawEnemies(gameWindow);
}

/*void GameManager::manageCollisions() {
    for (auto& proj : projectileManager.getProjectiles()) {
        collisionManager.manageCollision(playerManager.getPlayer(), proj);
        for (auto& enemy: enemyManager->getEnemies()) {
            collisionManager.manageCollision(enemy, proj);
        }
    }
    for (auto& enemy: enemyManager->getEnemies()) {
        collisionManager.manageCollision(playerManager.getPlayer(), enemy);
    }
}*/


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
        mapManager.drawMap(gameWindow, currentGameState);
        //entityManager.updateEntities(deltaTime);
        //enemyManager->update(deltaTime);
        update(deltaTime);
        //enemyManager->drawEnemies(gameWindow);
        //entityManager.drawEntities(gameWindow);
        collisionManager.manageCollisions(this, deltaTime);
        draw();
        gameWindow.setView(defaultView);
        uiManager.updateActiveUI(currentGameState);
        uiManager.drawUI(gameWindow, currentGameState); // UI elements are drwan based on the current state of the game
        gameWindow.display();
    }
}