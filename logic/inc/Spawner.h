#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include "../../core/inc/GameplayInfoSource.h"
#include "../inc/EnemyManager.h"
#include "../../factory/inc/EnemyFactory.h"
#include "../../factory/inc/EntityBuilder.h"
#include "../../core/inc/Event.h"
#include "../inc/SpawnRule.h"

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
