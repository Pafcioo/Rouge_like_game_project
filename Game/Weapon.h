#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Weapon {
private:
    float weaponFireCooldown;
    float timeSinceLastShot;
public:
    Weapon(float fireRate = 0.5f)
        : weaponFireCooldown(fireRate), timeSinceLastShot(0.f) {}
    ~Weapon() = default;
    void shoot(sf::Vector2f position, sf::Vector2f velocity, float speed); //Shooting new projectiles
    void update(float deltaTime);
};
