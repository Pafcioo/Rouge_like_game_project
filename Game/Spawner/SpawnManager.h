#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Game/Spawner/Spawner.h"
#include "Game/Spawner/SpawnStrategy.h"
#include "Game/Event.h"
#include "Game/Spawner/SpawnComponent.h"

struct EnemyParams {
        int health;
        float speed;
        sf::Vector2f position;
        std::string texturePath;
        std::shared_ptr<AIControllerDifficulty> difficulty;
        TimeBasedRule::TimeRule rule;
};

class SpawnManager
{
    private:
        std::vector<std::shared_ptr<SpawnStrategy>> strategies;
    public:
        SpawnManager();
        ~SpawnManager() = default;
        void addStrategy(std::shared_ptr<SpawnStrategy> strategy);
        void setUpStrategies(std::shared_ptr<GameplayInfoSource> gameplayInfoSource, std::shared_ptr<EnemyManager> enemyManager);
        void update(float deltaTime);
};