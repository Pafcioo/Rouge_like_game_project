#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {
    entityWeapon = std::make_shared<BasicWeapon>();
}

void Player::move(const sf::Vector2f direction)
{
    this->entitySprite.move(direction*entityCurrentSpeed);
    entityPosition = entitySprite.getPosition();
    gameplayInfo->setInfo<sf::Vector2f>("playerPos",entityPosition);
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
    entityWeapon->shoot(initialPosition, direction);
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





