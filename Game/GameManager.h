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

// The most important class of the game, that handles everything
class GameManager : public std::enable_shared_from_this<GameManager>
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<UIManager> uiManager;
    MapManager mapManager;
    sf::Font font;
    sf::View defaultView;
    sf::View gameplayView;
    std::shared_ptr<StateManager> stateManager;
    std::shared_ptr<SpawnManager> spawnManager;
    std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
    std::shared_ptr<EnemyManager> enemyManager;
public:
    GameManager();
    ~GameManager() = default;
    sf::Font& getFont();
    std::shared_ptr<UIManager> getUIManager();
    MapManager& getMapManager();
    EntityManager& getEntityManager();
    InputManager& getInputManager();
    std::shared_ptr<EventBus> getEventBus();
    sf::RenderWindow& getGameWindow();
    sf::View& getDefaultView();
    sf::View& getGameplayView();
    std::shared_ptr<StateManager> getStateManager();
    std::shared_ptr<SpawnManager> getSpawnManager();
    std::shared_ptr<GameplayInfoSource> getGameplayInfoSource();
    std::shared_ptr<EnemyManager> getEnemyManager();
    void setStateManager();
    void changeGameplayViewBasedOnPlayer();
    void Play();
};
