#include <iostream>
#include "Game/Spawner/SpawnManager.h"

SpawnManager::SpawnManager(){

};

void SpawnManager::addStrategy(std::shared_ptr<SpawnStrategy> strategy)
{
    strategies.push_back(strategy);
}

void SpawnManager::update(float deltaTime)
{
    for (auto& strategy : strategies)
    {
        strategy->executeStrategy(deltaTime);
    }
}