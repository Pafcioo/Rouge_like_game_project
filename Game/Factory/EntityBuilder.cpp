#include <iostream>
#include "EntityBuilder.h"
#include "Game/Spawner/SpawnRule.h"

void EnemyBuilder::reset(std::shared_ptr<SpawnConfig> config, std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    auto entityConfig = std::dynamic_pointer_cast<EnemySpawnConfig>(config);
    if (!entityConfig)
    {
        std::cerr << "Invalid config type for EnemyBuilder" << std::endl;
        return;
    }
    enemy = enemyFactory->createEntity(
        entityConfig->getHealth(),
        entityConfig->getSpeed(),
        entityConfig->getPosition(),
        *entityConfig->getTexture()
    );
}

void EnemyBuilder::setWeapon(std::shared_ptr<Weapon> weapon) const
{
    enemy->setWeapon(weapon);
}

void EnemyBuilder::setItem(std::shared_ptr<Item> item) const
{
    enemy->setItem(item);
}

void EnemyBuilder::setAbility(std::shared_ptr<Ability> ability) const
{
    enemy->setAbility(ability);
}

void EnemyBuilder::setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty) const
{
    auto controller = std::make_shared<EnemyAIController>(enemy,gameplayInfo);
    difficulty->setAIController(controller);
    difficulty->execute();
    if (auto enemyBuilt = std::dynamic_pointer_cast<Enemy>(enemy))
    {
        enemyBuilt->setDifficulty(difficulty);
        enemyBuilt->setEnemyController(controller);
    }
}

std::shared_ptr<Entity> EnemyBuilder::getEnemy() const 
{
  return enemy;
}
