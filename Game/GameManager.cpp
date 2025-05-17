#include "GameManager.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

GameManager::GameManager() : uiManager(*this),font("Assets/Roboto_Condensed-Black.ttf")
{
    eventBus = std::make_shared<EventBus>();
    spawnManager = std::make_unique<SpawnManager>(eventBus);
    uiManager.initAllUI(eventBus, font);
    entityManager.subscribeToEvents(eventBus);
    currentGameState = GameState::MainMenu;
    defaultView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    gameplayView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    gameplayInfoSource = std::make_shared<GameplayInfoSource>();
    enemyManager = std::make_shared<EnemyManager>();
    setUpSpawner();
}

void GameManager::setUpSpawner() {
    // Create spawn rules
    std::shared_ptr<SpawnRule> timeRule = std::make_shared<TimeBasedRule>(
        std::vector<TimeBasedRule::TimeRule>{
            {2.f, "enemy1"}, // Spawn enemy1 after 2 seconds
        }
    );
    EnemyConfig enemyConfig = {100, 50.f, {0.f, 0.f}, nullptr}; // Example enemy config
    gameplayInfoSource->setInfo<EnemyConfig>("enemy1", enemyConfig);
    // Add the spawn rule to the spawn manager
    spawnManager->addSpawnRule(timeRule);
    std::shared_ptr<AbstractSpawner> spawner = std::make_shared<Spawner>(eventBus, gameplayInfoSource, enemyManager);
    std::shared_ptr<EnemyFactory> factory = std::make_shared<BasicEnemyFactory>();
    spawner->registerFactory("enemy1", factory);
    spawnManager->setSpawner(spawner);
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
        mapManager.drawMap(gameWindow, currentGameState);
        entityManager.updateEntities(deltaTime);
        entityManager.drawEntities(gameWindow);
        gameWindow.setView(defaultView);
        uiManager.updateActiveUI(currentGameState);
        uiManager.drawUI(gameWindow, currentGameState); // UI elements are drwan based on the current state of the game
        
        gameWindow.display();
    }
}