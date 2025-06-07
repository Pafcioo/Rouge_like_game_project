#pragma once
#include <SFML/Graphics.hpp>
#include "Game/EntityManager.h"
#include "Game/InputManager.h"
#include "Game/UI/UIManager.h"
#include "Game/Player.h"
#include "Game/Event.h"
#include "Game/GameMap.h"
#include "Game/MapManager.h"

class StateManager;
class SpawnManager;
class GameplayInfoSourceManager;
class EnemyManager;
class ViewManager;

// Central game coordinator - manages all subsystems and their interactions
class GameManager : public std::enable_shared_from_this<GameManager>
{
private:
    // Core systems
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    MapManager mapManager;
    
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

public:
    GameManager();
    ~GameManager() = default;
    
    // Resource getters
    sf::Font& getFont();
    sf::RenderWindow& getGameWindow();
    std::shared_ptr<EventBus> getEventBus();
    
    // System getters
    std::shared_ptr<UIManager> getUIManager();
    MapManager& getMapManager();
    EntityManager& getEntityManager();
    InputManager& getInputManager();
    std::shared_ptr<StateManager> getStateManager();
    std::shared_ptr<SpawnManager> getSpawnManager();
    std::shared_ptr<GameplayInfoSource> getGameplayInfoSource();
    std::shared_ptr<EnemyManager> getEnemyManager();
    std::shared_ptr<ViewManager> getViewManager();
    
    // Game lifecycle
    void initStateManager();
    void Play();  // Main game loop entry point
};