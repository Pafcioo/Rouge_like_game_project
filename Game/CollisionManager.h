#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

class CollisionManager {
public:
    CollisionManager() = default;
    ~CollisionManager() = default;
    void manageCollision(Entity* entity, Projectile* projectile);
    void manageCollision(Entity* entity1, Entity* entity2);
    void manageCollision(Entity* entity, sf::RectangleShape& wall, float deltaTime);
};