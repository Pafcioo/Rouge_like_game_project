#pragma once
#include <SFML/Graphics.hpp>
#include "SpawnRule.h"

class AbstractSpawner;

class SpawnStrategy
{
    private:
        std::shared_ptr<AbstractSpawner> spawner;
        std::shared_ptr<SpawnRule> spawnRule;
        std::shared_ptr<SpawnConfig> spawnConfig;
    public:
        SpawnStrategy(std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnRule> spawnRule, std::shared_ptr<SpawnConfig> spawnConfig)
            :spawner(spawner), spawnRule(spawnRule), spawnConfig(spawnConfig){};
        ~SpawnStrategy(){};
        void executeStrategy(float deltaTime)
        {
            spawnRule->update(deltaTime, spawner, spawnConfig);
        }
};