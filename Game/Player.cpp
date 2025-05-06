#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

float Player::getEntitySpeed() {return entitySpeed;}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction);
    entityPosition = entitySprite.getPosition();
}

void Player::attack(sf::Vector2f direction)
{
    gun.shoot(entityPosition, direction, 500);
}


