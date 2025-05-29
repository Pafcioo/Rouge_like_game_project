#include <SFML/Graphics.hpp>
#include "Projectile.h"

sf::FloatRect Projectile::getGlobalBounds() {
    return projectileShape.getGlobalBounds();
}

bool Projectile::isActive() const {
    return projectileIsActive;
}

void Projectile::deactivate() {
    projectileIsActive = false;
}

sf::Vector2f Projectile::getInitialPosition() const {
    return projectileInitialPosition;
}

sf::CircleShape Projectile::getShape() const {
    return projectileShape;
}

void Projectile::update(float deltaTime) {
    projectileShape.move(projectileVelocity*deltaTime*projectileSpeed);
}

float Projectile::getDamage() const {
    return projectileDamage;
}

