#include <iostream>
#include "Spawner.h"

// EnemySpawner constructor: initializes base members
EnemySpawner::EnemySpawner(std::shared_ptr<EventBus> eventBus,
                           std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                           std::shared_ptr<EnemyManager> enemyManager)
{
    this->eventBus = eventBus;
    this->gameplayInfoSource = gameplayInfoSource;
    this->enemyManager = enemyManager;
}

// ZombieSpawner constructor: calls base and sets up specifics
ZombieSpawner::ZombieSpawner(std::shared_ptr<EventBus> eventBus,
                             std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                             std::shared_ptr<EnemyManager> enemyManager)
    : EnemySpawner(eventBus, gameplayInfoSource, enemyManager)
{
    sf::Texture* texture = new sf::Texture("Assets/ability1.png");
    gameplayInfoSource->setInfo<EntityConfig>("Zombie", EntityConfig{100, 50.f, {0.f, 0.f}, texture});
    factory = std::make_shared<ZombieFactory>();
    spawnRule = std::make_shared<TimeBasedRule>(
        TimeBasedRule::TimeRule{2.f, 5.f, 10.f, "Zombie"}
    );
    spawnRule->setSpawner(this);
}

void EnemySpawner::spawn(const std::string& entityType)
{
    auto config = gameplayInfoSource->getInfo<EntityConfig>(entityType);
    auto builder = std::make_shared<EnemyBuilder>(factory);
    builder->reset(config);
    auto enemy = builder->getEnemy();
    enemyManager->addEnemy(enemy);
    std::cout << "Spawned enemy of type: " << entityType << " at position: "
              << config.position.x << ", " << config.position.y << std::endl;

    std::vector<SpawnInfo> spawns;
    if (gameplayInfoSource->hasInfo("spawns")) {
        spawns = gameplayInfoSource->getInfo<std::vector<SpawnInfo>>("spawns");
    }
    spawns.push_back(SpawnInfo{entityType, config.position});
    gameplayInfoSource->setInfo("spawns", spawns);
}

void EnemySpawner::update(float deltaTime)
{
    if (spawnRule) {
        spawnRule->update(deltaTime, eventBus);
    }
}