#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include <vector>

// Forward declaration of classes
class EventBus;
enum class GameState;

class EntityManager
{
    private:
        Entity* player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
        bool isEntityManagerActive = false; // Bolean responsible for managing input for UI
    public:
        EntityManager() = default;
        ~EntityManager() = default;
        static std::vector<Projectile*> projectiles;
        void drawEntities(sf::RenderWindow& window);
        void updateEntityManager(GameState currentState);
        void updateEntities(float deltaTime);
        void subscribeToEvents(std::shared_ptr<EventBus> eventBus);
        Entity* getPlayer() { return player; }
};
