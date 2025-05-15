#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <math.h>

float Player::getEntitySpeed() {return entitySpeed;}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction*entitySpeed);
    entityPosition = entitySprite.getPosition();
}

void Player::attack(sf::Vector2f direction)
{
    sf::Vector2f initialPosition;
    // Projectiles are shot outside player bounds, otherwise they would immediately deactivate
    initialPosition.x = entityPosition.x + (static_cast<float>(entityTexture.getSize().x)/2.f * entitySprite.getScale().x + 10) * direction.x;
    initialPosition.y = entityPosition.y + (static_cast<float>(entityTexture.getSize().y)/2.f * entitySprite.getScale().y + 10) * direction.y;
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
    }
    gun.shoot(initialPosition, direction, 100);
}


