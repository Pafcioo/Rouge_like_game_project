#include <iostream>
#include "Game/Spawner/SpawnManager.h"
#include "Game/MapManager.h"

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

std::vector<sf::Vector2f> SpawnManager::createSpawnPositions(const sf::Vector2f& mapSize, float offset) {
    return {
        // Top edge spawners
        {-mapSize.x/2, -mapSize.y/2 - offset},  // Top left
        {0, -mapSize.y/2 - offset},             // Top center 
        {mapSize.x/2, -mapSize.y/2 - offset},   // Top right

        // Bottom edge spawners
        {-mapSize.x/2, mapSize.y/2 + offset},   // Bottom left
        {0, mapSize.y/2 + offset},              // Bottom center
        {mapSize.x/2, mapSize.y/2 + offset},    // Bottom right

        // Left and right edges
        {-mapSize.x/2 - offset, 0},             // Left center
        {mapSize.x/2 + offset, 0}               // Right center
    };
}

std::vector<std::shared_ptr<AIControllerDifficulty>> SpawnManager::createDifficulties() {
    return {
        std::make_shared<EasyAIControllerDifficulty>(),
        std::make_shared<BalancedAIControllerDifficulty>(),
        std::make_shared<DifficultAIControllerDifficulty>()
    };
}

std::vector<TimeBasedRule::TimeRule> SpawnManager::createTimeRules() {
    return {
        {3.f, 15.f, -1.f},    // Slow spawning
        {1.f, 10.f, -1.f},    // Medium spawning
        {0.5f, 5.f, -1.f}    // Fast spawning
    };
}

void SpawnManager::setupEnemies(
    const std::vector<sf::Vector2f>& positions,
    const std::vector<std::shared_ptr<AIControllerDifficulty>>& difficulties,
    const std::vector<TimeBasedRule::TimeRule>& timeRules,
    std::shared_ptr<AbstractSpawner> spawner,
    const EnemyParams& baseParams
) {
    for (size_t i = 0; i < positions.size(); i++) {
        auto difficulty = difficulties[i % difficulties.size()];
        auto timeRule = timeRules[i % timeRules.size()];

        EnemyParams params(
            baseParams.baseHealth,
            baseParams.baseSpeed,
            baseParams.texturePath,
            baseParams.healthIncrement,
            baseParams.speedIncrement,
            positions[i],  // Use position from the array
            difficulty,    // Use cycling difficulty
            baseParams.weapon,
            timeRule      // Use cycling time rule
        );

        auto config = std::make_shared<EnemySpawnConfig>(
            params.getScaledHealth(i),
            params.getScaledSpeed(i),
            params.position,
            new sf::Texture(params.texturePath)
        );
        
        config->add(std::make_shared<DifficultyComponent>(params.difficulty));
        config->add(std::make_shared<WeaponComponent>(params.weapon));
        auto rule = std::make_shared<TimeBasedRule>(params.rule);
        
        addStrategy(std::make_shared<SpawnStrategy>(spawner, rule, config));
    }
}

void SpawnManager::setUpStrategies(std::shared_ptr<GameplayInfoSource> gameplayInfoSource, 
                                 std::shared_ptr<EnemyManager> enemyManager, 
                                 std::shared_ptr<MapManager> mapManager) {
    const auto& currentMap = mapManager->getCurrentMap();
    sf::Vector2f mapSize = currentMap.getSize();
    float offset = 200.f;

    auto spawnPositions = createSpawnPositions(mapSize, offset);
    auto difficulties = createDifficulties();
    auto timeRules = createTimeRules();

    // Define different enemy types with their base parameters
    std::vector<std::pair<std::shared_ptr<AbstractSpawner>, EnemyParams>> enemyTypes = {
        // Basic zombies - slow but tough
        {std::make_shared<ZombieSpawner>(gameplayInfoSource, enemyManager),
         EnemyParams(2, 20.f, "Assets/zombie.png", 0.5, 5.f, {}, nullptr, 
                    nullptr, TimeBasedRule::TimeRule())},
         
        // Fast zombies - very fast but weak
        {std::make_shared<ZombieSpawner>(gameplayInfoSource, enemyManager),
         EnemyParams(1, 40.f, "Assets/zombie_soldier.png", 0.25, 10.f, {}, nullptr, 
                    std::make_shared<BasicWeapon>(), TimeBasedRule::TimeRule())},
    };

    // Setup all types of enemies
    for (const auto& [spawner, baseParams] : enemyTypes) {
        setupEnemies(spawnPositions, difficulties, timeRules, spawner, baseParams);
    }
}