#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ProjectileManager {
public:
    ProjectileManager() = default;
    ~ProjectileManager() = default;
    void updateProjectiles(float deltaTime);
    void drawProjectiles(sf::RenderWindow& window);
    static std::vector<Projectile*> projectiles;
    std::vector<Projectile*> getProjectiles();
};