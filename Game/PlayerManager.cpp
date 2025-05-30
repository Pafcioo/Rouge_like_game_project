#include <iostream>
#include "PlayerManager.h"
#include "Event.h"
#include "GameManager.h"
#include <algorithm>
#include <cmath>

PlayerManager::PlayerManager()
{
    player = new Player(100, 250, {0, 0}, sf::Texture("Assets/player.png"));
    isEntityManagerActive = false;
}

void PlayerManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
    player->setGameplayInfo(gameplayInfo);
}

//std::vector<Projectile*> EntityManager::projectiles;
// Method for subscribing events where player subscribe to events like movement and attack
void PlayerManager::subscribeToEvents(std::shared_ptr<EventBus> eventBus)
{
    eventBus->subscribe<MoveEvent>([this](const MoveEvent& moveEvent) {
        if (player && isEntityManagerActive) {
            player->move(moveEvent.direction * moveEvent.deltaTime);
            player->setEntityDirection(moveEvent.direction);
        }
    });
    eventBus->subscribe<AttackEvent>([this](const AttackEvent& attackEvent) {
        if (player && isEntityManagerActive) {
            if (attackEvent.direction != sf::Vector2f(0, 0)) {
                player->setEntityDirection(attackEvent.direction);
            }
            player->attack(player->getEntityDirection());
        }
    });
    eventBus->subscribe<useAbilityEvent>([this](const useAbilityEvent&) {
        if (player && isEntityManagerActive) {
            player->useAbility();
        }
    });
}

void PlayerManager::drawEntities(sf::RenderWindow& window)
{
    // Placeholder for drawing entities
    // In a real implementation, you would loop through your entities and draw them here
    if(isEntityManagerActive){
        window.draw(*player);
        /*for (auto& proj : projectiles) {
            window.draw(*proj);
        }*/
    }
    //std::cout << "Drawing entities..." << std::endl;
}

void PlayerManager::updateEntities(float deltaTime) {
    
    player->update(deltaTime);
    /*for (auto& proj : projectiles) {
        proj->update(deltaTime);
        double distance = sqrt(pow(proj->getShape().getPosition().x - proj->getInitialPosition().x, 2) + pow(proj->getShape().getPosition().y - proj->getInitialPosition().y, 2));
        if (distance > 500) {
            proj->deactivate();
        }
    }*/

    // Delete inactive projectiles
    /*projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [](const Projectile* p) { return !p->isActive(); }),
        projectiles.end()
    );*/
}
// Method for changing the activity of entity manager, which is only active when the game is in playing state
void PlayerManager::updateEntityManager(GameState currentState){
    if(currentState == GameState::Playing)
    {
        isEntityManagerActive = true;
    }
    else{
        isEntityManagerActive = false;
    }
}

Entity* PlayerManager::getPlayer() {return player;}