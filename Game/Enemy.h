#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AIController/AIController.h"

class Enemy : public Entity
{
    private:
        //std::unique_ptr<AbstractAIController> enemyController;
    public:
    Enemy(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}
    ~Enemy() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
};

class Zombie : public Enemy
{
    public:
        Zombie(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            Enemy(health, speed, position, texture) {}
        ~Zombie() override = default;
        void move(sf::Vector2f direction) override;
        void attack(sf::Vector2f direction) override;
        void update(float deltaTime) override {}
        void useItem(std::shared_ptr<Item> item) override {}
        void useAbility() override {}
};