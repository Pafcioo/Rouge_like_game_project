#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Game/GameplayInfoSource.h"
#include <vector>

// Forward declaration of classes
class EventBus;

class PlayerManager
{
    private:
        Entity* player;
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
    public:
        PlayerManager();
        ~PlayerManager() = default;
        void draw(sf::RenderTarget& target);
        void update(float deltaTime);
        void subscribeToEvents(std::shared_ptr<EventBus> eventBus);
        void unsubscribeToEvents(std::shared_ptr<EventBus> eventBus);
        void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        Entity* getPlayer();
};
