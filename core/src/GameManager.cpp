#include <iostream>
#include "../inc/GameManager.h"
#include "../../entity/inc/Entity.h"
#include "../../entity/inc/Player.h"
#include "../../entity/inc/Projectile.h"
#include "../../logic/inc/EnemyManager.h"
#include "../inc/GameplayInfoSource.h"
#include "../inc/StateManager.h"
#include "../../logic/inc/SpawnManager.h"
#include "../../logic/inc/ViewManager.h"
#include "../../logic/inc/PlayerManager.h"
#include "../../logic/inc/ProjectileManager.h"
#include "../../logic/inc/CollisionManager.h"

// Constructor initializes all core game systems and managers
GameManager::GameManager() : font("resources/fonts/Roboto_Condensed-Black.ttf")
{
    // Bus for events in game
    eventBus = std::make_shared<EventBus>();
    inputManager = std::make_shared<InputManager>(eventBus, gameWindow);
    // View set up
    viewManager = std::make_shared<ViewManager>();
    // Source for all game info like level, hp, position of player...
    fileManager = std::make_shared<FileManager>("../../resources/data/GameData.txt");
    gameplayInfoSource = std::make_shared<GameplayInfoSource>();

    // Managers for entities like player and enemy
    playerManager = std::make_shared<PlayerManager>();
    playerManager->setGameplayInfo(gameplayInfoSource);
    playerManager->setEventBus(eventBus);
    enemyManager = std::make_shared<EnemyManager>();
    enemyManager->setGameplayInfo(gameplayInfoSource);
    // Managers for projectiles and colisions
    projectileManager = std::make_shared<ProjectileManager>();
    collisionManager = std::make_shared<CollisionManager>();

    mapManager = std::make_shared<MapManager>();
    // Spawner set up
    spawnManager = std::make_shared<SpawnManager>();
    
    // UIManager set up
    uiManager = std::make_shared<UIManager>();
}


// Initialize state manager after construction (requires shared_from_this)
void GameManager::initStateManager()
{
    // Create state manager with dependencies
    stateManager = std::make_shared<StateManager>(uiManager, shared_from_this(), eventBus);
    stateManager->subscribeToEvents();
    
    // Set up initial menu state
    auto newState = std::make_shared<InMenu>();
    newState->setEventBus(eventBus);
    newState->setUIManager(uiManager);
    newState->setGameManager(shared_from_this());
    stateManager->pushState(newState);
}

// Getter methods for accessing game resources and managers
sf::Font& GameManager::getFont()
{
    return font;
}

std::shared_ptr<UIManager> GameManager::getUIManager() {
    return uiManager;
}

std::shared_ptr<MapManager> GameManager::getMapManager() {
    return mapManager;
}

std::shared_ptr<EventBus> GameManager::getEventBus() {
    return eventBus;
}

std::shared_ptr<InputManager> GameManager::getInputManager() {
    return inputManager;
}

sf::RenderWindow& GameManager::getGameWindow() {
    return gameWindow;
}

std::shared_ptr<StateManager> GameManager::getStateManager() {
    return stateManager;
}

std::shared_ptr<SpawnManager> GameManager::getSpawnManager() {
    return spawnManager;
}

std::shared_ptr<GameplayInfoSource> GameManager::getGameplayInfoSource() {
    return gameplayInfoSource;
}

std::shared_ptr<EnemyManager> GameManager::getEnemyManager() {
    return enemyManager;
}

std::shared_ptr<ViewManager> GameManager::getViewManager() {
    return viewManager;
}

std::shared_ptr<PlayerManager> GameManager::getPlayerManager() {
    return playerManager;
}

std::shared_ptr<ProjectileManager> GameManager::getProjectileManager() {
    return projectileManager;
}

std::shared_ptr<CollisionManager> GameManager::getCollisionManager() {
    return collisionManager;
}

std::shared_ptr<FileManager> GameManager::getFileManager() {
    return fileManager;
}

// Main game loop - handles window creation, timing, and rendering
void GameManager::Play()
{
    // Create SFML window with 720p resolution and 60 fps limit
    gameWindow.create(sf::VideoMode({1280, 720}), "SFML Game");
    gameWindow.setFramerateLimit(60);
    initStateManager();
    // Main game loop
    while (gameWindow.isOpen())
    {
        // Calculate delta time for frame-independent movement
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        // Cap delta time to prevent large jumps (e.g., during debugging pauses)
        if(deltaTime > 1/60.f) deltaTime = 1.f / 60.f; 
        
        // Clear, update, draw, and display frame
        gameWindow.clear();
        stateManager->update(deltaTime);
        stateManager->draw(gameWindow);
        gameWindow.display();
    }
    
}