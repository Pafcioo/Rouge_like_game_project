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

void SpawnManager::setUpStrategies(std::shared_ptr<GameplayInfoSource> gameplayInfoSource, std::shared_ptr<EnemyManager> enemyManager)
{
    std::vector<EnemyParams> zombieParams = {
        {100, 250.f, {500.f, 0.f}, "Assets/ability1.png", std::make_shared<DifficultAIControllerDifficulty>(), std::make_shared<BasicWeapon>(), {5.f, 2.f, 6.f}},
        {120, 200.f, {-500.f, 0.f}, "Assets/ability1.png", std::make_shared<EasyAIControllerDifficulty>(), std::make_shared<BasicWeapon>(), {5.f, 1.f, 7.f}}
    };
    // Zombies spawner
    auto zombieSpawner = std::make_shared<ZombieSpawner>(gameplayInfoSource, enemyManager);
    for (const auto& params : zombieParams) {
        auto config = std::make_shared<EnemySpawnConfig>(params.health, params.speed, params.position, new sf::Texture(params.texturePath));
        config->add(std::make_shared<DifficultyComponent>(params.difficulty));
        config->add(std::make_shared<WeaponComponent>(params.weapon));
        auto rule = std::make_shared<TimeBasedRule>(params.rule);
        addStrategy(std::make_shared<SpawnStrategy>(
            zombieSpawner,
            rule,
            config
        ));
    }
    // Other spawners...
}