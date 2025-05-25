#include <iostream>
#include "EnemyFactory.h"

ZombieFactory::ZombieFactory(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
}

std::shared_ptr<Entity> ZombieFactory::createEntity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture)
{
    auto result = std::make_shared<Zombie>(health, speed, position, texture);
    result->setGameplayInfo(gameplayInfo);
    result->setAIController();
    return result;
}