#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <cmath>

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction*entityCurrentSpeed);
    entityPosition = entitySprite.getPosition();
}

void Player::attack(sf::Vector2f direction)
{
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
    }
    entityWeapon->shoot(entityPosition, direction, 500);
}

void Player::useItem(std::shared_ptr<Item> item) {
    item->activate(this);
    item->setIsUsed(true);
}

void Player::useAbility() {
    entityAbility->activate();
}

void Player::update(float deltaTime) {
    entityWeapon->update(deltaTime);
    entityAbility->update(deltaTime);
    entityAbility->influence(this);
}





