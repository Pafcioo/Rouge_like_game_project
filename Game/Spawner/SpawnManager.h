#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <string>
#include "Game/Spawner/Spawner.h"
#include "Game/Spawner/SpawnStrategy.h"
#include "Game/Event.h"
#include "Game/Spawner/SpawnComponent.h"
#include "Game/Spawner/SpawnRule.h"

// Forward declarations for types used as pointers/references
class GameplayInfoSource;
class EnemyManager;
class AIControllerDifficulty;

struct EnemyParams {
    int health;
    float speed;
    sf::Vector2f position;
    std::string texturePath;
    std::shared_ptr<AIControllerDifficulty> difficulty;
    std::shared_ptr<Weapon> weapon;
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