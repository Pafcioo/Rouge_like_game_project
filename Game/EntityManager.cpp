#include <iostream>
#include "EntityManager.h"
#include "Event.h"
#include "GameManager.h"
#include <algorithm>
#include <cmath>

EntityManager::EntityManager()
{
    player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
    player->setGameplayInfo(gameplayInfo);
    isEntityManagerActive = false;
}

void EntityManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
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
}

void EntityManager::drawEntities(sf::RenderWindow& window)
{
    // Placeholder for drawing entities
    // In a real implementation, you would loop through your entities and draw them here
    if(isEntityManagerActive){
        window.draw(*player);
        for (auto& proj : projectiles) {
            window.draw(*proj);
        }
    }
    //std::cout << "Drawing entities..." << std::endl;
}

void EntityManager::updateEntities(float deltaTime) {
    
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
// Method for changing the activity of entity manager, which is only active when the game is in playing state
void EntityManager::updateEntityManager(GameState currentState){
    if(currentState == GameState::Playing)
    {
        isEntityManagerActive = true;
    }
    else{
        isEntityManagerActive = false;
    }
}
