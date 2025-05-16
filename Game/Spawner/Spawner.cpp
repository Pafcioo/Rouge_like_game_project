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
    if (factoryIt != factories.end()) {
        enemyManager->addEnemy(factoryIt->second->createEnemy(
            config.health,
            config.speed,
            config.position,
            *config.texture
        ));
    } else {
        std::cerr << "No factory registered for enemy type: " << enemyType << std::endl;
    }
}