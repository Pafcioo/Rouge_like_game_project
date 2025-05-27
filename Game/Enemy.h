#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game/AIController/AIController.h"

class Enemy : public Entity, public std::enable_shared_from_this<Enemy>
{
    private:
        std::shared_ptr<AIControllerDifficulty> enemyDifficulty;
        std::shared_ptr<AbstractAIController> enemyController;
    public:
    Enemy(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Enemy() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
    void setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty);
    void setEnemyController(std::shared_ptr<AbstractAIController> controller);
    void update(float deltaTime);
};

class Zombie : public Enemy
{
    public:
        Zombie(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
        ~Zombie() override = default;
        void move(sf::Vector2f direction) override;
        void attack(sf::Vector2f direction) override;
        void useItem(std::shared_ptr<Item> item) override {}
        void useAbility() override {}
};