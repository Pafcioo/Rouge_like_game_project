#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"
#include <iostream>

void Enemy::move(sf::Vector2f direction)
{
    entitySprite.move(direction*entitySpeed);
    entityPosition = entitySprite.getPosition();
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

void Enemy::setAIController()
{
    enemyController = std::make_shared<EnemyAIController>(shared_from_this(),gameplayInfo);
    difficulty = std::make_unique<EasyAIControllerDifficulty>(enemyController);
    difficulty->execute();
}
void Enemy::update(float deltaTime)
{
    enemyController->update(deltaTime);
}

void Zombie::move(sf::Vector2f direction)
{
    Enemy::move(direction);
}

void Zombie::attack(sf::Vector2f direction)
{
    Enemy::attack(direction);
}

