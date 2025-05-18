#include <iostream>
#include "Game/Spawner/SpawnRule.h"
#include "Game/Spawner/Spawner.h"


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

int SpawnConfig::getHealth() const 
{
    return health; 
}

float SpawnConfig::getSpeed() const 
{
    return speed;
}

const sf::Vector2f& SpawnConfig::getPosition() const 
{
    return position;
}

sf::Texture* SpawnConfig::getTexture() const 
{
    return texture;
}