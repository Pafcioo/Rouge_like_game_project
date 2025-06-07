#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}

void Enemy::move(sf::Vector2f direction)
{
    entitySprite.move(direction*entityCurrentSpeed);
    entityPosition = entitySprite.getPosition();
}

void Enemy::attack(sf::Vector2f direction)
{
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
    }
    entityWeapon->shoot(entityPosition, direction);
}

void Enemy::setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty)
{
    enemyDifficulty = difficulty;
}

void Enemy::setEnemyController(std::shared_ptr<AbstractAIController> controller)
{
    enemyController = controller;
}

void Enemy::update(float deltaTime)
{
    enemyController->update(deltaTime);
}

Zombie::Zombie(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            Enemy(health, speed, position, texture) {}

void Zombie::move(sf::Vector2f direction)
{
    Enemy::move(direction);
}

void Zombie::attack(sf::Vector2f direction)
{
    Enemy::attack(direction);
}

