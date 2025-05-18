#include <iostream>
#include "Game/Spawner/SpawnRule.h"
#include "Game/Spawner/Spawner.h"
#include "Game/Factory/EntityBuilder.h"


void TimeBasedRule::update(float deltaTime, std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnConfig> config)
{
    timeRule.spawnTime -= deltaTime;
    timeRule.endTime -= deltaTime;
    // Check if the end time has been reached
    if (timeRule.endTime >= 0) {
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

void EnemySpawnConfig::configureBuilder(std::shared_ptr<EntityBuilder> builder)
{
    if(auto enemyBuilder = std::dynamic_pointer_cast<EnemyBuilder>(builder))
    {
        enemyBuilder->reset(std::make_shared<EnemySpawnConfig>(health, speed, position, texture));
    }
};