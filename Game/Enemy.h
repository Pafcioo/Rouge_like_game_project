#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AIController/AIController.h"

class Enemy : public Entity
{
    private:
        //std::unique_ptr<AbstractAIController> enemyController;
    public:
    Enemy(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Enemy() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
};

class Zombie : public Enemy
{
    public:
        Zombie(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
        ~Zombie() override = default;
        void move(sf::Vector2f direction) override;
        void attack(sf::Vector2f direction) override;
        void update(float deltaTime) override {}
        void useItem(std::shared_ptr<Item> item) override {}
        void useAbility() override {}
};