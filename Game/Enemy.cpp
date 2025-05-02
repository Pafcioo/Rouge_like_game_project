#include <SFML/Graphics.hpp>
#include "Enemy.h"

void Enemy::move(sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Enemy::attack(sf::Vector2f direction)
{
    //Future implementation
}

