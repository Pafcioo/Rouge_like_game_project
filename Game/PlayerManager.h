#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Game/GameplayInfoSource.h"
#include <vector>

// Forward declaration of classes
class EventBus;
enum class GameState;

class PlayerManager
{
    private:
        Entity* player;
        bool isEntityManagerActive; // Bolean responsible for managing input for UI
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
    public:
        PlayerManager();
        ~PlayerManager() = default;
        //static std::vector<Projectile*> projectiles;
        void drawEntities(sf::RenderWindow& window);
        void updateEntityManager(GameState currentState);
        void updateEntities(float deltaTime);
        void subscribeToEvents(std::shared_ptr<EventBus> eventBus);
        void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        Entity* getPlayer();
};
