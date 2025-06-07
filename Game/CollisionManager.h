#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Projectile.h"

class GameManager;

class CollisionManager {
public:
    CollisionManager() = default;
    ~CollisionManager() = default;
    void manageCollision(Entity* entity, Projectile* proj);
    void manageCollision(std::shared_ptr<Entity> entity, Projectile* proj);
    void manageCollision(Entity* entity1, std::shared_ptr<Entity>& entity2);
    void manageCollision(Entity* entity, sf::RectangleShape& wall, float deltaTime);
    void manageCollisions(std::shared_ptr<GameManager> gameManager, float deltaTime);
};
