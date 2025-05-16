#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity
{
    private:
        std::unique_ptr<AbstractAIController> enemyController;
    public:
    Enemy(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {}
    ~Enemy() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
};