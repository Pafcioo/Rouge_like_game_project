#include <iostream>
#include "Game/Spawner/Spawner.h"

// EnemySpawner constructor: initializes base members
EnemySpawner::EnemySpawner(std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                           std::shared_ptr<EnemyManager> enemyManager)
{
    this->gameplayInfoSource = gameplayInfoSource;
    this->enemyManager = enemyManager;
}

void EnemySpawner::spawn(std::shared_ptr<SpawnConfig> config)
{
    auto enemyConfig = std::dynamic_pointer_cast<EnemySpawnConfig>(config);
    if (!enemyConfig)
    {
        std::cerr << "Invalid config type for EnemyBuilder" << std::endl;
        return;
    }
    auto builder = std::make_shared<EnemyBuilder>(factory);
    enemyConfig->configureBuilder(builder);
    enemyManager->addEnemy(builder->getEnemy());
}

// ZombieSpawner constructor: calls base and sets up specifics
ZombieSpawner::ZombieSpawner(std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                             std::shared_ptr<EnemyManager> enemyManager)
    : EnemySpawner(gameplayInfoSource, enemyManager)
{
    factory = std::make_shared<ZombieFactory>();
}

void ZombieSpawner::spawn(std::shared_ptr<SpawnConfig> config)
{
    EnemySpawner::spawn(config);
    std::cout << "Zombie spawned at position: " << config->getPosition().x << ", " << config->getPosition().y << std::endl;
}


