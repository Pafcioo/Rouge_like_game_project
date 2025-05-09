#include <iostream>
#include "EntityManager.h"
#include "Event.h"
#include <algorithm>
#include <cmath>

std::vector<Projectile*> EntityManager::projectiles;

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
    // Subscribe to attack and movement events to control movement of player and his attack
    eventBus.subscribe<MoveEvent>([this, deltaTime](const MoveEvent& moveEvent){
        player->move(moveEvent.direction*deltaTime);
    });
    eventBus.subscribe<AttackEvent>([this, deltaTime](const AttackEvent& attackEvent){
        player->attack(attackEvent.direction*deltaTime);
    });

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
