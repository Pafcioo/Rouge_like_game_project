#include "CollisionManager.h"
#include <SFML/Graphics.hpp>

void CollisionManager::manageCollision(Entity* entity, Projectile* proj) {
    if (proj->getGlobalBounds().findIntersection(entity->getEntityGlobalBounds())) {
        proj->deactivate();
    }
}

void CollisionManager::manageCollision(Entity* entity, sf::RectangleShape& wall, float deltaTime) {
    if (wall.getGlobalBounds().findIntersection(entity->getEntityGlobalBounds())) {
        float dx = abs(wall.getPosition().x - entity->getEntityPosition().x);
        float dy = abs(wall.getPosition().y - entity->getEntityPosition().y);
        if (dx > dy) {
            if (entity->getEntityPosition().x > wall.getPosition().x) {
                entity->move(sf::Vector2f(1, 0)*deltaTime*entity->getEntitySpeed());
            } else {
                entity->move(sf::Vector2f(-1, 0)*deltaTime*entity->getEntitySpeed());
            }
        } else {
            if (entity->getEntityPosition().y > wall.getPosition().y) {
                entity->move(sf::Vector2f(0, 1)*deltaTime*entity->getEntitySpeed());
            }
            else {
                entity->move(sf::Vector2f(0, -1)*deltaTime*entity->getEntitySpeed());
            }
        }
    }
}