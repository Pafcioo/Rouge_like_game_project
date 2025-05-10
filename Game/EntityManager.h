#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include <vector>

class EventBus;
enum class GameState;

class EntityManager
{
    private:
        Entity* player = new Player(100, 250, {640, 360}, sf::Texture("Assets/player.png"));
        bool isEntityManagerActive = false;
    public:
        EntityManager() = default;
        ~EntityManager() = default;
        static std::vector<Projectile*> projectiles;
        void drawEntities(sf::RenderWindow& window);
        void updateEntityManager(GameState currentState);
        void updateEntities(float deltaTime, EventBus& eventBus);
        void subscribeToEvents(EventBus& eventBus);
        Entity* getPlayer() { return player; }
};
