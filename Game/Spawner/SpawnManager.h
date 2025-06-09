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
class MapManager;

struct EnemyParams {
    // Base stats
    int baseHealth;
    float baseSpeed;
    std::string texturePath;
    
    // Scaling factors
    float healthIncrement;
    float speedIncrement;
    
    // Position and components
    sf::Vector2f position;
    std::shared_ptr<AIControllerDifficulty> difficulty;
    std::shared_ptr<Weapon> weapon;
    TimeBasedRule::TimeRule rule;

    // Constructor for easier initialization
    EnemyParams(
        int _baseHealth, 
        float _baseSpeed,
        const std::string& _texturePath,
        float _healthInc,
        float _speedInc,
        const sf::Vector2f& _pos,
        std::shared_ptr<AIControllerDifficulty> _diff,
        std::shared_ptr<Weapon> _weapon,
        TimeBasedRule::TimeRule _rule
    ) : baseHealth(_baseHealth),
        baseSpeed(_baseSpeed),
        texturePath(_texturePath),
        healthIncrement(_healthInc),
        speedIncrement(_speedInc),
        position(_pos),
        difficulty(_diff),
        weapon(_weapon),
        rule(_rule) {}

    // Helper method to get scaled stats based on index
    int getScaledHealth(size_t index) const {
        return baseHealth + (static_cast<int>(index) * healthIncrement);
    }

    float getScaledSpeed(size_t index) const {
        return baseSpeed + (index * speedIncrement);
    }
};

class SpawnManager
{
    private:
        std::vector<std::shared_ptr<SpawnStrategy>> strategies;
        std::vector<sf::Vector2f> createSpawnPositions(const sf::Vector2f& mapSize, float offset);
        std::vector<std::shared_ptr<AIControllerDifficulty>> createDifficulties();
        std::vector<TimeBasedRule::TimeRule> createTimeRules();
        void setupEnemies(
            const std::vector<sf::Vector2f>& positions,
            const std::vector<std::shared_ptr<AIControllerDifficulty>>& difficulties,
            const std::vector<TimeBasedRule::TimeRule>& timeRules,
            std::shared_ptr<AbstractSpawner> spawner,
            const EnemyParams& baseParams
        );
    public:
        SpawnManager();
        ~SpawnManager() = default;
        void addStrategy(std::shared_ptr<SpawnStrategy> strategy);
        void setUpStrategies(std::shared_ptr<GameplayInfoSource> gameplayInfoSource, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<MapManager> mapManager);
        void update(float deltaTime);
};