#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include <algorithm>
#include <iostream>

void Weapon::update(float deltaTime) {
    timeSinceLastShot += deltaTime;

    // Update projectiles
    for (Projectile* proj : weaponProjectiles) {
        proj->update(deltaTime);
    }

    // Delete inactive projectiles
    weaponProjectiles.erase(
        std::remove_if(weaponProjectiles.begin(), weaponProjectiles.end(),
                       [](const Projectile* p) { return !p->isActive(); }),
        weaponProjectiles.end()
    );
}

void Weapon::shoot(sf::Vector2f position, sf::Vector2f velocity, float speed) {
    if (timeSinceLastShot >= weaponFireCooldown) {
        std::cout << "Shooting..." << std::endl;
        weaponProjectiles.emplace_back(new Projectile(position, velocity, speed));
        timeSinceLastShot = 0.f;
    }
}

void Weapon::draw(sf::RenderWindow &window) {
    //std::cout << "Drawing projectiles..." << std::endl;
    for (Projectile* proj : weaponProjectiles) {
        window.draw(*proj);
    }
}

