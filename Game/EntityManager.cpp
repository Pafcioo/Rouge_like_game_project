#include <iostream>
#include "EntityManager.h"
#include "Event.h"
#include "GameManager.h"
#include <algorithm>
#include <cmath>

EntityManager::EntityManager()
{
    player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
    isEntityManagerActive = false;
}

void EntityManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    player->setGameplayInfo(gameplayInfo);
}

std::vector<Projectile*> EntityManager::projectiles;
// Method for subscribing events where player subscribe to events like movement and attack
void EntityManager::subscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->subscribe<MoveEvent>([this](const MoveEvent& moveEvent) {
        if (player && isEntityManagerActive) {
            player->move(moveEvent.direction * moveEvent.deltaTime);
        }
    });
    eventBus->subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player && attackEvent.direction!=sf::Vector2f(0,0) && isEntityManagerActive) {
            player->attack(attackEvent.direction);
        }
    });
    eventBus->subscribe<useAbilityEvent>([this](const useAbilityEvent&) {
        if (player && isEntityManagerActive) {
            player->useAbility();
        }
    });
}

void EntityManager::unsubscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->unsubscribeAll<MoveEvent>();
    eventBus->unsubscribeAll<AttackEvent>();
    eventBus->unsubscribeAll<useAbilityEvent>();
}

void EntityManager::drawEntities(sf::RenderTarget& target)
{
    target.draw(*player);
    for (auto& proj : projectiles) {
        target.draw(*proj);
    }
}

void EntityManager::updateEntities(float deltaTime) {
    
    player->update(deltaTime);
    for (auto& proj : projectiles) {
        proj->update(deltaTime);
        double distance = sqrt(pow(proj->getShape().getPosition().x - proj->getInitialPosition().x, 2) + pow(proj->getShape().getPosition().y - proj->getInitialPosition().y, 2));
        if (distance > 500) {
            proj->deactivate();
        }
    }

    // Delete inactive projectiles
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [](const Projectile* p) { return !p->isActive(); }),
        projectiles.end()
    );
}

void EntityManager::setActivity(bool activity)
{
    isEntityManagerActive = activity;
}

Entity* EntityManager::getPlayer() {return player;}