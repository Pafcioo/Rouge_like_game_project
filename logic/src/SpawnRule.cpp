#include <iostream>
#include <algorithm>
#include "../inc/SpawnRule.h"
#include "../inc/Spawner.h"
#include "../../factory/inc/EntityBuilder.h"
#include "../inc/SpawnComponent.h"
#include "../../core/inc/GameplayInfoSource.h"

void TimeBasedRule::update(float deltaTime, std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnConfig> config)
{
    timeRule.spawnTime -= deltaTime;
    
    // Only decrease endTime if it's positive (finite duration)
    if (timeRule.endTime > 0) {
        timeRule.endTime -= deltaTime;
    }

    // Spawn if either endTime is negative (infinite) or hasn't reached zero yet
    if (timeRule.endTime < 0 || timeRule.endTime >= 0) {
        if (timeRule.spawnTime <= 0) {
            if (spawner) {
                spawner->spawn(config);
            }
            timeRule.spawnTime += timeRule.spawnInterval;
        }
    }
}

const sf::Vector2f& SpawnConfig::getPosition() const 
{
    return position;
}

int EntitySpawnConfig::getHealth() const 
{
    return health; 
}

float EntitySpawnConfig::getSpeed() const 
{
    return speed;
}

sf::Texture* EntitySpawnConfig::getTexture() const 
{
    return texture;
}

void EntitySpawnConfig::add(std::shared_ptr<SpawnComponent> component) {
    components.push_back(component);
}
void EntitySpawnConfig::remove(std::shared_ptr<SpawnComponent> component) {
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void EnemySpawnConfig::configureBuilder(std::shared_ptr<EntityBuilder> builder, std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    if(auto enemyBuilder = std::dynamic_pointer_cast<EnemyBuilder>(builder))
    {
        enemyBuilder->reset(std::make_shared<EnemySpawnConfig>(health, speed, position, texture), gameplayInfoSource);
        for (const auto& component : components) {
            component->apply(builder);
        }
    }
};