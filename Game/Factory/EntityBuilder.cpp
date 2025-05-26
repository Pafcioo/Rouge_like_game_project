#include <iostream>
#include "EntityBuilder.h"
#include "Game/Spawner/SpawnRule.h"

void EnemyBuilder::reset(std::shared_ptr<SpawnConfig> config)
{
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

std::shared_ptr<Entity> EnemyBuilder::getEnemy() const {return enemy;}