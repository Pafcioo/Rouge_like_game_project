#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

float Player::getEntitySpeed() {return entitySpeed;}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction);
    entityPosition += direction;
}

void Player::attack(sf::Vector2f direction)
{
    gun.shoot(entityPosition, direction, 500);
}

void Player::updateGun(float deltaTime) {
    gun.update(deltaTime);
}

void Player::drawProjectiles(sf::RenderWindow& window) {
    gun.draw(window);
}


