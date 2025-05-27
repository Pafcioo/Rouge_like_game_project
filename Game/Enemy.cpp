#include <SFML/Graphics.hpp>
#include "Enemy.h"

Enemy::Enemy(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}

void Enemy::move(sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Enemy::attack(sf::Vector2f direction)
{
    //Future implementation
}

Zombie::Zombie(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            Enemy(health, speed, position, texture) {}

void Zombie::move(sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Zombie::attack(sf::Vector2f direction)
{
    //Future implementation
}

