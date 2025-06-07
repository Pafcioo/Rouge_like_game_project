#include <iostream>
#include "Game/PlayerManager.h"
#include "Game/Event.h"
#include "Game/GameManager.h"
#include <algorithm>
#include <cmath>

PlayerManager::PlayerManager()
{
    player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
}

void PlayerManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    player->setGameplayInfo(gameplayInfo);
}

// Method for subscribing events where player subscribe to events like movement and attack
void PlayerManager::subscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->subscribe<MoveEvent>([this](const MoveEvent& moveEvent) {
        if (player) {
            player->move(moveEvent.direction * moveEvent.deltaTime);
            player->setEntityDirection(moveEvent.direction);
        }
    });
    eventBus->subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player) {
            if (attackEvent.direction != sf::Vector2f(0, 0)) {
                player->setEntityDirection(attackEvent.direction);
            }
            player->attack(player->getEntityDirection());
        }
    });
    eventBus->subscribe<useAbilityEvent>([this](const useAbilityEvent&) {
        if (player) {
            player->useAbility();
        }
    });
}

void PlayerManager::unsubscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->unsubscribeAll<MoveEvent>();
    eventBus->unsubscribeAll<AttackEvent>();
    eventBus->unsubscribeAll<useAbilityEvent>();
}

void PlayerManager::draw(sf::RenderTarget& target)
{
    target.draw(*player);
}

void PlayerManager::update(float deltaTime) 
{
    player->update(deltaTime);
}

Entity* PlayerManager::getPlayer() {return player;}