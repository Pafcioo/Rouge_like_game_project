#pragma once
#include <SFML/Graphics.hpp>
#include "core/inc/InputManager.h"
#include "ui/inc/UIManager.h"
#include "entity/inc/Player.h"
#include "core/inc/Event.h"
#include "core/inc/GameMap.h"
#include "core/inc/MapManager.h"
#include "core/inc/FileManager.h"

class StateManager;
class SpawnManager;
class GameplayInfoSourceManager;
class EnemyManager;
class ViewManager;
class PlayerManager;
class ProjectileManager;
class CollisionManager;

// Central game coordinator - manages all subsystems and their interactions
class GameManager : public std::enable_shared_from_this<GameManager>
{
private:
    // Core systems
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<MapManager> mapManager;
    
    // Shared resources
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<UIManager> uiManager;
    sf::Font font;
    
    // Game subsystems
    std::shared_ptr<ViewManager> viewManager;
    std::shared_ptr<StateManager> stateManager;
    std::shared_ptr<SpawnManager> spawnManager;
    std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<PlayerManager> playerManager;
    std::shared_ptr<ProjectileManager> projectileManager;
    std::shared_ptr<CollisionManager> collisionManager;
    std::shared_ptr<FileManager> fileManager;
public:
    GameManager();
    ~GameManager() = default;
    
    // Resource getters
    sf::Font& getFont();
    sf::RenderWindow& getGameWindow();
    std::shared_ptr<EventBus> getEventBus();
    std::shared_ptr<InputManager> getInputManager();
    
    // System getters
    std::shared_ptr<UIManager> getUIManager();
    std::shared_ptr<MapManager> getMapManager();
    std::shared_ptr<StateManager> getStateManager();
    std::shared_ptr<SpawnManager> getSpawnManager();
    std::shared_ptr<GameplayInfoSource> getGameplayInfoSource();
    std::shared_ptr<EnemyManager> getEnemyManager();
    std::shared_ptr<ViewManager> getViewManager();
    std::shared_ptr<PlayerManager> getPlayerManager();
    std::shared_ptr<ProjectileManager> getProjectileManager();
    std::shared_ptr<CollisionManager> getCollisionManager();
    std::shared_ptr<FileManager> getFileManager();
    
    // Game lifecycle
    void initStateManager();
    void Play();  // Main game loop entry point
};