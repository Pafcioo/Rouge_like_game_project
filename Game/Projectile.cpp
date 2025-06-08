#include <SFML/Graphics.hpp>
#include "Projectile.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f velocity, float speed, float damage, const std::type_info* type, float radius, sf::Color color):
        projectileInitialPosition(position), projectileVelocity(velocity), projectileSpeed(speed), projectileIsActive(true), projectileType(type) {
    projectileShape.setRadius(radius);
    projectileShape.setFillColor(color);
    projectileShape.setOrigin({radius, radius});
    projectileShape.setPosition(projectileInitialPosition);
    projectileDamage = damage;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(projectileShape, states);
}

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

const std::type_info *Projectile::getProjectileType() {
    return projectileType;
}
