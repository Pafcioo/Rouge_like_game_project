#include "GameManager.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Game/Spawner/EnemyManager.h"
#include "Game/GameplayInfoSource.h"
#include "Game/States/StateManager.h"
#include "Game/Spawner/SpawnManager.h"

GameManager::GameManager() : font("Assets/Roboto_Condensed-Black.ttf")
{
    // Bus for events in game
    eventBus = std::make_shared<EventBus>();
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
    spawnManager = std::make_shared<SpawnManager>();
    spawnManager->setUpStrategies(gameplayInfoSource,enemyManager);
    // UIManager set up
    uiManager = std::make_shared<UIManager>();
}

void GameManager::setStateManager()
{
    stateManager = std::make_shared<StateManager>(uiManager, shared_from_this(), eventBus);
    stateManager->subscribeToEvents();
    auto newState = std::make_shared<InMenu>();
    newState->setEventBus(eventBus);
    newState->setUIManager(uiManager);
    newState->setGameManager(shared_from_this());
    stateManager->pushState(newState);
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

sf::Font& GameManager::getFont()
{
    return font;
}

std::shared_ptr<UIManager> GameManager::getUIManager() {
    return uiManager;
}

MapManager& GameManager::getMapManager() {
    return mapManager;
}

EntityManager& GameManager::getEntityManager() {
    return entityManager;
}

InputManager& GameManager::getInputManager() {
    return inputManager;
}

std::shared_ptr<EventBus> GameManager::getEventBus() {
    return eventBus;
}

sf::RenderWindow& GameManager::getGameWindow() {
    return gameWindow;
}

sf::View& GameManager::getDefaultView() {
    return defaultView;
}

sf::View& GameManager::getGameplayView() {
    return gameplayView;
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

void GameManager::Play()
{
    // Create a window
    gameWindow.create(sf::VideoMode({1280, 720}), "SFML Game");
    gameWindow.setFramerateLimit(60);
    setStateManager();
    
    // Main loop
    while (gameWindow.isOpen())
    {
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        if(deltaTime > 1/60.f) deltaTime = 1.f / 60.f; 
        gameWindow.clear();
        stateManager->update(deltaTime);
        stateManager->draw(gameWindow);
        gameWindow.display();
    }
}