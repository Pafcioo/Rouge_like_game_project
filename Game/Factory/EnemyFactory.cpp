#include <iostream>
#include "EnemyFactory.h"

std::shared_ptr<Enemy> BasicEnemyFactory::createEnemy(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture)
{
    return std::make_shared<Enemy>(health, speed, position, texture);
}