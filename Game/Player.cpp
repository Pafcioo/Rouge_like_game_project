#include <SFML/Graphics.hpp>
#include "Player.h"

float Player::getEntitySpeed() {return entitySpeed;}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Player::attack()
{
    //Future implementation
}
