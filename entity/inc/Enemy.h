#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "../../algorithm/inc/AIController.h"

class Enemy : public Entity, public std::enable_shared_from_this<Enemy>
{
    private:
        std::shared_ptr<AIControllerDifficulty> enemyDifficulty;
        std::shared_ptr<AbstractAIController> enemyController;
    public:
    Enemy(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Enemy() override = default;
    void setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty);
    void setEnemyController(std::shared_ptr<AbstractAIController> controller);
    void update(float deltaTime) override;
};

class Zombie : public Enemy
{
    public:
        Zombie(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
        ~Zombie() override = default;
};