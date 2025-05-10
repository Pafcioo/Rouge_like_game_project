#include <iostream>
#include "EntityManager.h"
#include "Event.h"
#include <algorithm>
#include <cmath>

std::vector<Projectile*> EntityManager::projectiles;

void EntityManager::subscribeToEvents(EventBus& eventBus)
{
    std::cout << "Subscribing to MoveEvent..." << std::endl;
    eventBus.subscribe<MoveEvent>([this](const MoveEvent& moveEvent) {
        if (player) {
            player->move(moveEvent.direction * moveEvent.deltaTime);
        }
    });
    std::cout << "Subscribing to AttackEvent..." << std::endl;
    eventBus.subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player && attackEvent.direction!=sf::Vector2f(0,0)) {
            player->attack(attackEvent.direction);
        }
    });
}

void EntityManager::drawEntities(sf::RenderWindow& window)
{
    // Placeholder for drawing entities
    // In a real implementation, you would loop through your entities and draw them here
    window.draw(*player);
    for (auto& proj : projectiles) {
        window.draw(*proj);
    }
    //std::cout << "Drawing entities..." << std::endl;
}

void EntityManager::updateEntities(float deltaTime, EventBus& eventBus) {
    
    player->getWeapon()->update(deltaTime);
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
