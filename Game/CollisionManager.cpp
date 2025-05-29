#include "CollisionManager.h"
#include <SFML/Graphics.hpp>

void CollisionManager::manageCollision(Entity* entity, Projectile* proj) {
    if (proj->getGlobalBounds().findIntersection(entity->getEntityGlobalBounds())) {
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

void CollisionManager::manageCollision(std::shared_ptr<Entity> entity, Projectile *proj) {
    if (proj->getGlobalBounds().findIntersection(entity->getEntityGlobalBounds())) {
        entity->setHealth(entity->getHealth()-proj->getDamage());
        proj->deactivate();
    }
}

