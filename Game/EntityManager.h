#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Game/GameplayInfoSource.h"
#include <vector>

// Forward declaration of classes
class EventBus;

class EntityManager
{
    private:
        Entity* player;
        bool isEntityManagerActive; // Bolean responsible for managing input for UI
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
    public:
        EntityManager();
        ~EntityManager() = default;
        static std::vector<Projectile*> projectiles;
        void drawEntities(sf::RenderTarget& target);
        void setActivity(bool activity);
        void updateEntities(float deltaTime);
        void subscribeToEvents(std::shared_ptr<EventBus> eventBus);
        void unsubscribeToEvents(std::shared_ptr<EventBus> eventBus);
        void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        Entity* getPlayer();
};
