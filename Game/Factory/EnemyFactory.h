#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Enemy.h"

class EntityFactory
{
    public:
        EntityFactory() = default;
        virtual ~EntityFactory() = default;

        virtual std::shared_ptr<Entity> createEntity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture) = 0;
};

class EnemyFactory: public EntityFactory
{
    public:
        virtual ~EnemyFactory() = default;
        virtual std::shared_ptr<Entity> createEntity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture) = 0;
};

class ZombieFactory : public EnemyFactory
{
    public:
        ZombieFactory() = default;
        ~ZombieFactory() override = default;
        std::shared_ptr<Entity> createEntity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture) override;
};