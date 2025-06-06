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
    auto intersection = entity->getEntityGlobalBounds().findIntersection(wall.getGlobalBounds());
    if (intersection.has_value()) {
        // Intersection area
        sf::FloatRect overlap = intersection.value();

        // Depth of intersection in both axes
        float overlapX = overlap.size.x;
        float overlapY = overlap.size.y;

        float pushX = 0.0f;
        float pushY = 0.0f;

        //Choose axis with smaller intersection
        if (overlapX < overlapY) {
            pushX = (entity->getPosition().x < wall.getPosition().x) ? -1 : 1;
        } else {
            pushY = (entity->getPosition().y < wall.getPosition().y) ? -1 : 1;
        }

        entity->move(sf::Vector2f(pushX, pushY) * deltaTime);

        std::cout << "Collision detected" << std::endl;
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
    for (auto& barrier : gameManager->getBarriers()) {
        manageCollision(gameManager->getPlayerManager().getPlayer(), barrier, deltaTime);
    }
}


