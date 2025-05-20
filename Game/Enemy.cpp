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

void Zombie::move(sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Zombie::attack(sf::Vector2f direction)
{
    //Future implementation
}

