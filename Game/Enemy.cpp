#include <SFML/Graphics.hpp>
#include "Enemy.h"

void Enemy::move(sf::Vector2f direction)
{
    entitySprite.move(direction);
}

void Enemy::attack(sf::Vector2f direction)
{
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
    }
    gun.shoot(entityPosition, direction, 500);
}

void Zombie::move(sf::Vector2f direction)
{
    Enemy::move(direction);
}

void Zombie::attack(sf::Vector2f direction)
{
    Enemy::attack(direction);
}

