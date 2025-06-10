#include <SFML/Graphics.hpp>
#include "Enemy.h"

Enemy::Enemy(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}


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
    Entity::update(deltaTime);
    enemyController->update(deltaTime);
}

Zombie::Zombie(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
    Enemy(health, speed, position, texture) {}


