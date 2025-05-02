#include <SFML/Graphics.hpp>
#include "Player.h"

float Player::getEntitySpeed() {return entitySpeed;}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Player::attack(sf::Vector2f direction)
{
    gun.shoot(entityPosition, direction, 100);
}

void Player::updateGun(float deltaTime, sf::RenderWindow& window) {
    gun.update(deltaTime);
    gun.draw(window);
}

