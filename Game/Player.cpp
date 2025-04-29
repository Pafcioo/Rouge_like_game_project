#include <SFML/Graphics.hpp>
#include "Player.h"

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction);
}

void Player::attack()
{
    //Future implementation
}
