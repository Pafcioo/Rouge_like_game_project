#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Game/GameplayInfoSource.h"
#include "EnemyManager.h"
#include "Game/Factory/EnemyFactory.h"
#include "Game/Factory/EntityBuilder.h"
#include "Game/Event.h"
#include "Game/Spawner/SpawnRule.h"
#include <unordered_map>

struct SpawnInfo {
    std::string entityType;
    sf::Vector2f position;
};

// Abstract base class
class AbstractSpawner {
protected:
    std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<EntityFactory> factory;
    std::shared_ptr<SpawnRule> spawnRule;
public:
    virtual ~AbstractSpawner() = default;
    virtual void spawn(const std::string& entityType) = 0;
    virtual void update(float deltaTime) = 0;
};

// Abstract enemy spawner
class EnemySpawner : public AbstractSpawner {
protected:
    std::shared_ptr<EnemyManager> enemyManager;
public:
    EnemySpawner(std::shared_ptr<EventBus> eventBus,
                 std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                 std::shared_ptr<EnemyManager> enemyManager);
    ~EnemySpawner() override = default;
    virtual void spawn(const std::string& entityType) override;
    virtual void update(float deltaTime) override;
};

// Concrete zombie spawner
class ZombieSpawner : public EnemySpawner {
public:
    ZombieSpawner(std::shared_ptr<EventBus> eventBus,
                  std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                  std::shared_ptr<EnemyManager> enemyManager);
    ~ZombieSpawner() override = default;
};
