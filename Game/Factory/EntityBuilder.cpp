#include <iostream>
#include "EntityBuilder.h"
#include "Game/Spawner/SpawnRule.h"

void EnemyBuilder::reset(std::shared_ptr<SpawnConfig> config, std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    auto entityConfig = std::dynamic_pointer_cast<EnemySpawnConfig>(config);
    if (!entityConfig)
    {
        std::cerr << "Invalid config type for EnemyBuilder" << std::endl;
        return;
    }
    enemy = enemyFactory->createEntity(
        entityConfig->getHealth(),
        entityConfig->getSpeed(),
        entityConfig->getPosition(),
        *entityConfig->getTexture()
    );
}

void EnemyBuilder::setWeapon() const
{
    // Future implementation
}

void EnemyBuilder::setItem() const
{
    // Future implementation
}

void EnemyBuilder::setAbility() const
{
    // Future implementation
}

void EnemyBuilder::setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty) const
{
    auto controller = std::make_shared<EnemyAIController>(enemy,gameplayInfo);
    difficulty->setAIController(controller);
    difficulty->execute();
    if (auto enemyBuilt = std::dynamic_pointer_cast<Enemy>(enemy))
    {
        enemyBuilt->setDifficulty(difficulty);
        enemyBuilt->setEnemyController(controller);
    }
}

