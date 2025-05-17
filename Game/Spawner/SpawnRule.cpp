#include <iostream>
#include "Game/Spawner/SpawnRule.h"
#include "Game/Spawner/Spawner.h"

void SpawnRule::setSpawner(AbstractSpawner* s) {
    spawner = s;
}

void TimeBasedRule::update(float deltaTime, std::shared_ptr<EventBus> eventBus)
{
    timeRule.spawnTime -= deltaTime;
    timeRule.endTime -= deltaTime;
    // Check if the end time has been reached
    if (timeRule.endTime >= 0) {
        if (timeRule.spawnTime <= 0) {
            if (spawner) {
                spawner->spawn(timeRule.labelOfSpawner);
            }
            timeRule.spawnTime += timeRule.spawnInterval;
        }
    }
}