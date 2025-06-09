#include "CollisionManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game/GameManager.h"
#include "Game/PlayerManager.h"
#include "Game/Spawner/EnemyManager.h"

CollisionManager::CollisionManager() {
    for (int i = 0; i < 4; i++) {
        barriers.emplace_back();
        barriers[i].setPosition(sf::Vector2f(5000, 5000));
    }
}

void CollisionManager::manageCollision(Entity* entity, Projectile* proj) {
    auto intersection = entity->getEntityGlobalBounds().findIntersection(proj->getShape().getGlobalBounds());
    if (intersection.has_value() && static_cast<std::type_index>(typeid(*entity)) != proj->getProjectileType()) {
        entity->setHealth(entity->getHealth()-proj->getDamage());
        proj->deactivate();
    }
}

std::pair<bool, bool> operator< (Entity* entity, sf::RectangleShape& wall) {
    bool x = entity->getPosition().x < wall.getPosition().x;
    bool y = entity->getPosition().y < wall.getPosition().y;
    return {x, y};
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
            pushX = (entity < wall).first ? -1 : 1;
        } else {
            pushY = (entity < wall).second ? -1 : 1;
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
    if (intersection.has_value() && static_cast<std::type_index>(typeid(*entity)) != proj->getProjectileType()) {
        entity->setHealth(entity->getHealth()-proj->getDamage());
        proj->deactivate();
    }
}

void CollisionManager::manageCollisions(std::shared_ptr<GameManager> gameManager, float deltaTime) {
    for (auto& proj : gameManager->getProjectileManager()->getProjectiles()) {
        manageCollision(gameManager->getPlayerManager()->getPlayer(), proj);
        for (auto& enemy: gameManager->getEnemyManager()->getEnemies()) {
            manageCollision(enemy, proj);
        }
    }
    for (auto& enemy: gameManager->getEnemyManager()->getEnemies()) {
        manageCollision(gameManager->getPlayerManager()->getPlayer(), enemy);
    }
    if (!gameManager->getMapManager()->getCurrentMapLabel().empty()) {
        sf::Vector2f size = gameManager->getMapManager()->getCurrentMap().getSize();
        for (auto& barrier : barriers) {
            barrier.setSize(size);
            barrier.setOrigin(size / 2.f);
        }
        barriers[0].setPosition(sf::Vector2f(size.x, 0));
        barriers[1].setPosition(sf::Vector2f(-size.x, 0));
        barriers[2].setPosition(sf::Vector2f(0, size.y));
        barriers[3].setPosition(sf::Vector2f(0, -size.y));
    }
    for (auto& barrier : barriers) {
        manageCollision(gameManager->getPlayerManager()->getPlayer(), barrier, deltaTime);
    }
}


