#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "PlayerManager.h"
#include <iostream>

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
        //std::cout << "Shooting from position: " << position.x << " " << position.y << std::endl;
        ProjectileManager::projectiles.emplace_back(new Projectile(position, velocity, projSpeed, projDamage, type));
        //std::cout << type->name() << std::endl;
        timeSinceLastShot = 0.f;
    }
}

void Weapon::update(float deltaTime) {
    timeSinceLastShot += deltaTime;
}

