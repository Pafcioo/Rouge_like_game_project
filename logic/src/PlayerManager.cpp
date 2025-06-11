#include <iostream>
#include "../inc/PlayerManager.h"
#include "../../core/inc/Event.h"
#include "../../core/inc/GameManager.h"
#include "../../core/inc/GameState.h"
#include <algorithm>
#include <cmath>

PlayerManager::PlayerManager(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    player = new Player(100, 250, {0, 0}, sf::Texture("resources/images/player.png"));
    ItemBuilder* builder = new HealPotionBuilder();
    player->setItem(builder->build(gameplayInfoSource));
    delete builder;
    player->setAbility(std::make_shared<SprintAbility>());
    player->setWeapon(std::make_shared<BasicWeapon>());
    setGameplayInfo(gameplayInfoSource);
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
        }
    });
    eventBus->subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player) {
            if (attackEvent.direction != sf::Vector2f(0, 0)) {
                player->setEntityDirection(attackEvent.direction);
                player->attack(attackEvent.direction);
            }
        }
    });
    eventBus->subscribe<useAbilityEvent>([this](const useAbilityEvent&) {
        if (player) {
            player->useAbility();
        }
    });
    eventBus->subscribe<useItemEvent>([this](const useItemEvent&) {
        if (player) {
            player->useItem();
        }
    });
}

void PlayerManager::unsubscribeToEvents()
{
    eventBus->unsubscribeAll<MoveEvent>();
    eventBus->unsubscribeAll<AttackEvent>();
    eventBus->unsubscribeAll<useAbilityEvent>();
    eventBus->unsubscribeAll<useItemEvent>();
}

void PlayerManager::draw(sf::RenderTarget& target)
{
    target.draw(*player);
}

void PlayerManager::update(float deltaTime) 
{
    player->update(deltaTime);
    
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