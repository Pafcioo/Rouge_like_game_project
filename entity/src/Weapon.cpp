#include <SFML/Graphics.hpp>
#include "../inc/Weapon.h"
#include "../../logic/inc/PlayerManager.h"

Weapon::Weapon(float fireRate):
    weaponFireCooldown(fireRate), timeSinceLastShot(0.f) {}

std::string Weapon::getWeaponName() {
    return weaponName;
}


BasicWeapon::BasicWeapon(): Weapon(0.25f) {
    weaponName = "Basic Weapon";
    projSpeed = 500;
    projDamage = 10;
}

void BasicWeapon::shoot(sf::Vector2f position, sf::Vector2f velocity, std::type_index type) {
    
    if (timeSinceLastShot >= weaponFireCooldown) {
        ProjectileManager::projectiles.emplace_back(new Projectile(position, velocity, projSpeed, projDamage, type));
        timeSinceLastShot = 0.f;
    }
}

void Weapon::update(float deltaTime) {
    timeSinceLastShot += deltaTime;
}

