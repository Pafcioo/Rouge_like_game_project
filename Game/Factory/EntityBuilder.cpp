#include <iostream>
#include "EntityBuilder.h"
#include "Game/GameplayInfoSource.h"

void EnemyBuilder::reset(EntityConfig config)
{
    // Create an enemy entity
    enemy = enemyFactory->createEntity(
        config.health,
        config.speed,
        config.position,
        *config.texture
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

