#include "CollisionManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"

void CollisionManager::manageCollision(Entity* entity, Projectile* proj) {
    auto intersection = entity->getEntityGlobalBounds().findIntersection(proj->getShape().getGlobalBounds());
    if (intersection.has_value()) {
        entity->setHealth(entity->getHealth()-proj->getDamage());
        proj->deactivate();
    }
}

void CollisionManager::manageCollision(Entity* entity, sf::RectangleShape& wall, float deltaTime) {
    if (wall.getGlobalBounds().findIntersection(entity->getEntityGlobalBounds())) {
        float dx = abs(wall.getPosition().x - entity->getPosition().x);
        float dy = abs(wall.getPosition().y - entity->getPosition().y);
        if (dx > dy) {
            if (entity->getPosition().x > wall.getPosition().x) {
                entity->move(sf::Vector2f(1, 0)*deltaTime*entity->getEntitySpeed());
            } else {
                entity->move(sf::Vector2f(-1, 0)*deltaTime*entity->getEntitySpeed());
            }
        } else {
            if (entity->getPosition().y > wall.getPosition().y) {
                entity->move(sf::Vector2f(0, 1)*deltaTime*entity->getEntitySpeed());
            }
            else {
                entity->move(sf::Vector2f(0, -1)*deltaTime*entity->getEntitySpeed());
            }
        }
    }
}

void CollisionManager::manageCollision(Entity *entity1, std::shared_ptr<Entity>& entity2) {
    auto intersection = entity1->getEntityGlobalBounds().findIntersection(entity2->getEntityGlobalBounds());
    if (intersection.has_value()) {
        entity1->setHealth(entity1->getHealth()-1);
        entity2->setHealth(entity2->getHealth()-1);
        std::cout << "Collision detected" << std::endl;
    }
}


void CollisionManager::manageCollision(std::shared_ptr<Entity> entity, Projectile *proj) {
    auto intersection = entity->getEntityGlobalBounds().findIntersection(proj->getShape().getGlobalBounds());
    if (intersection.has_value()) {
        entity->setHealth(entity->getHealth()-proj->getDamage());
        proj->deactivate();
    }
}

void CollisionManager::manageCollisions(GameManager *gameManager, float deltaTime) {
    for (auto& proj : gameManager->getProjectileManager().getProjectiles()) {
        manageCollision(gameManager->getPlayerManager().getPlayer(), proj);
        for (auto& enemy: gameManager->getEnemyManager()->getEnemies()) {
            manageCollision(enemy, proj);
        }
    }
    for (auto& enemy: gameManager->getEnemyManager()->getEnemies()) {
        manageCollision(gameManager->getPlayerManager().getPlayer(), enemy);
    }
}


