#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "EntityManager.h"
#include <iostream>

Weapon::Weapon(float fireRate):
    weaponFireCooldown(fireRate), timeSinceLastShot(0.f) {}
void Weapon::shoot(sf::Vector2f position, sf::Vector2f velocity) {
    //std::cout << timeSinceLastShot << std::endl;
    if (timeSinceLastShot >= weaponFireCooldown) {
        std::cout << "Shooting from position: " << position.x << " " << position.y << std::endl;
        ProjectileManager::projectiles.emplace_back(new Projectile(position, velocity, projSpeed, projDamage));
        timeSinceLastShot = 0.f;
    }
}

void Weapon::update(float deltaTime) {
    timeSinceLastShot += deltaTime;
}

BasicWeapon::BasicWeapon(): Weapon(0.5f) {
    weaponName = "Basic Weapon";
    projSpeed = 500;
    projDamage = 20;
}

