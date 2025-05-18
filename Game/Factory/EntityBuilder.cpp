#include <iostream>
#include "EntityBuilder.h"
#include "Game/Spawner/SpawnRule.h"

void EnemyBuilder::reset(std::shared_ptr<SpawnConfig> config)
{
    // Create an enemy entity
    enemy = enemyFactory->createEntity(
        config->getHealth(),
        config->getSpeed(),
        config->getPosition(),
        *config->getTexture()
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

