#include <iostream>
#include "EnemyFactory.h"

std::shared_ptr<Entity> ZombieFactory::createEntity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture)
{
    return std::make_shared<Zombie>(health, speed, position, texture);
}