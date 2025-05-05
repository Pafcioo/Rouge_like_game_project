#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "EntityManager.h"
#include <iostream>

void Weapon::shoot(sf::Vector2f position, sf::Vector2f velocity, float speed) {
    //std::cout << timeSinceLastShot << std::endl;
    if (timeSinceLastShot >= weaponFireCooldown) {
        std::cout << "Shooting from position: " << position.x << " " << position.y << std::endl;
        EntityManager::projectiles.emplace_back(new Projectile(position, velocity, speed));
        timeSinceLastShot = 0.f;
    }
}

void Weapon::update(float deltaTime) {
    timeSinceLastShot += deltaTime;
}

