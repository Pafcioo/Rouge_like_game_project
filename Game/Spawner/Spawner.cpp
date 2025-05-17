#include <iostream>
#include "Spawner.h"

Spawner::Spawner(std::shared_ptr<EventBus> eventBus,
                std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                std::shared_ptr<EnemyManager> enemyManager)
    : AbstractSpawner()
{
    this->eventBus = eventBus;
    this->gameplayInfoSource = gameplayInfoSource;
    this->enemyManager = enemyManager;
    eventBus->subscribe<SpawnEvent>([this](const SpawnEvent& event) {
        spawn(event.labelOfSpawner);
    });
}

void Spawner::registerFactory(const std::string& enemyType, std::shared_ptr<EnemyFactory> factory)
{
    factories[enemyType] = factory;
}

void Spawner::spawn(const std::string& enemyType)
{
    auto config = gameplayInfoSource->getInfo<EnemyConfig>(enemyType);
    auto factoryIt = factories.find(enemyType);
    auto builder = std::make_shared<EnemyBuilder>(factoryIt->second);
    if (factoryIt != factories.end()) {
        builder->reset(config);
        auto enemy = builder->getEnemy();
        enemyManager->addEnemy(enemy);
        std::cout << "Spawned enemy of type: " << enemyType << " at position: " << config.position.x << ", " << config.position.y << std::endl;
    } else {
        std::cerr << "No factory registered for enemy type: " << enemyType << std::endl;
    }
    // Pobierz aktualną listę (lub utwórz nową jeśli nie istnieje)
    auto spawns = gameplayInfoSource->getInfo<std::vector<SpawnInfo>>("spawns");
    spawns.push_back(SpawnInfo{enemyType, config.position});
    gameplayInfoSource->setInfo("spawns", spawns);
}