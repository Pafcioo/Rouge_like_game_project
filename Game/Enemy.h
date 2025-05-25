#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game/AIController/AIController.h"

class Enemy : public Entity, public std::enable_shared_from_this<Enemy>
{
    private:
        std::unique_ptr<AIControllerDifficulty> difficulty;
        std::shared_ptr<AbstractAIController> enemyController;
    public:
    Enemy(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}
    ~Enemy() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
    void setAIController();
    void update(float deltaTime);
};

class Zombie : public Enemy
{
    public:
        Zombie(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            Enemy(health, speed, position, texture) {}
        ~Zombie() override = default;
        void move(sf::Vector2f direction) override;
        void attack(sf::Vector2f direction) override;
        float getEntitySpeed() override { return entitySpeed; }
};