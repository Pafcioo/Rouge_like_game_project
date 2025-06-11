#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../entity/inc/Entity.h"
#include "../../entity/inc/Player.h"
#include "../../entity/inc/Projectile.h"
#include "../../core/inc/GameplayInfoSource.h"

// Forward declaration of classes
class EventBus;

class PlayerManager
{
    private:
        Entity* player;
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
        std::shared_ptr<EventBus> eventBus;
    public:
        PlayerManager(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        ~PlayerManager() = default;
        void draw(sf::RenderTarget& target);
        void update(float deltaTime);
        void subscribeToEvents();
        void unsubscribeToEvents();
        void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        void setEventBus(std::shared_ptr<EventBus> eventBus);
        Entity* getPlayer();
        std::shared_ptr<GameplayInfoSource> getGameplayInfo();
};
