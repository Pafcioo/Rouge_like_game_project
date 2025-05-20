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

// Abstract base class
class AbstractSpawner {
protected:
    std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
    std::shared_ptr<EntityFactory> factory;
public:
    virtual ~AbstractSpawner() = default;
    virtual void spawn(std::shared_ptr<SpawnConfig> config) = 0;
};

// Abstract enemy spawner
class EnemySpawner : public AbstractSpawner {
protected:
    std::shared_ptr<EnemyManager> enemyManager;
public:
    EnemySpawner(std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                 std::shared_ptr<EnemyManager> enemyManager);
    ~EnemySpawner() override = default;
    virtual void spawn(std::shared_ptr<SpawnConfig> config) override;
};

// Concrete zombie spawner
class ZombieSpawner : public EnemySpawner {
public:
    ZombieSpawner(std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                  std::shared_ptr<EnemyManager> enemyManager);
    ~ZombieSpawner() override = default;
    virtual void spawn(std::shared_ptr<SpawnConfig> config) override;
};
