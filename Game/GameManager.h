#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Button.h"
#include "Player.h"
#include "Event.h"
#include "GameMap.h"
#include "MapManager.h"
#include "Game/Spawner/SpawnManager.h"
#include "Game/GameplayInfoSource.h"
#include "Game/Spawner/EnemyManager.h"
#include "ProjectileManager.h"
#include <memory>
#include "CollisionManager.h"
// The most important class of the game, that handles everything
class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    PlayerManager playerManager;
    InputManager inputManager;
    std::shared_ptr<EventBus> eventBus;
    UIManager uiManager;
    MapManager mapManager;
    sf::Font font;
    GameState currentGameState;
    sf::View defaultView;
    sf::View gameplayView;
    std::unique_ptr<SpawnManager> spawnManager;
    std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
    std::shared_ptr<EnemyManager> enemyManager;
    ProjectileManager projectileManager;
    CollisionManager collisionManager;
public:
    GameManager();
    ~GameManager(){};
    void changeGameState(GameState newState);
    UIManager getUIManager();
    GameState getGameState() const;
    MapManager& getMapManager();
    PlayerManager& getPlayerManager();
    ProjectileManager& getProjectileManager();
    std::shared_ptr<EnemyManager> getEnemyManager();
    void changeGameplayViewBasedOnPlayer();
    void update(float deltaTime);
    void draw();
    void manageCollisions();
    void Play();
};
