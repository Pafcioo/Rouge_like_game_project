#include <iostream>
#include "Game/PlayerManager.h"
#include "Game/Event.h"
#include "Game/GameManager.h"
#include "Game/States/GameState.h"
#include <algorithm>
#include <cmath>

PlayerManager::PlayerManager()
{
    player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
    ItemBuilder* builder = new HealPotionBuilder();
    player->setItem(builder->build());
    delete builder;
    player->setAbility(std::make_shared<SprintAbility>());
    player->setWeapon(std::make_shared<BasicWeapon>());
}

void PlayerManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    player->setGameplayInfo(gameplayInfo);
    gameplayInfo->setInfo("playerInitialHealth", player->getHealth());
}

void PlayerManager::setEventBus(std::shared_ptr<EventBus> eventBus)
{
    this->eventBus = eventBus;
}

// Method for subscribing events where player subscribe to events like movement and attack
void PlayerManager::subscribeToEvents()
{
    eventBus->subscribe<MoveEvent>([this](const MoveEvent& moveEvent) {
        if (player) {
            player->move(moveEvent.direction * moveEvent.deltaTime);
            //player->setEntityDirection(moveEvent.direction);
        }
    });
    eventBus->subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player) {
            if (attackEvent.direction != sf::Vector2f(0, 0)) {
                player->setEntityDirection(attackEvent.direction);
                player->attack(attackEvent.direction);
            }
            //player->attack(player->getEntityDirection());
        }
    });
    eventBus->subscribe<useAbilityEvent>([this](const useAbilityEvent&) {
        if (player) {
            player->useAbility();
        }
    });
}

void PlayerManager::unsubscribeToEvents()
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
    
    // Add these lines to update the ability cooldown info
    if (auto ability = player->getAbility()) {
        gameplayInfo->setInfo("playerAbilityCooldown", ability->getCurrentCooldown());
        gameplayInfo->setInfo("playerAbilityMaxCooldown", ability->getCooldown());
    }
    
    if(player->getHealth() <= 0)
    {
        eventBus->publish(ChangeStateEvent{std::make_shared<GameOver>()});
        gameplayInfo->setInfo("Deaths", gameplayInfo->getInfo<int>("Deaths") + 1);
    }
}

Entity* PlayerManager::getPlayer() {return player;}

std::shared_ptr<GameplayInfoSource> PlayerManager::getGameplayInfo() {
    return gameplayInfo;
}