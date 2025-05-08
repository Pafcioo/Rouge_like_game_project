#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include <vector>

class EventBus;

class EntityManager
{
    private:
        Entity* player = new Player(100, 250, {640, 360}, sf::Texture("Assets/player.png"));
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        static std::vector<Projectile*> projectiles;
        void drawEntities(sf::RenderWindow& window);
        void updateEntities(float deltaTime, EventBus& eventBus);
        Entity* getPlayer() { return player; }

};
