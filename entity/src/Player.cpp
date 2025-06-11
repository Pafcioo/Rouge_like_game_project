#include <cmath>
#include <SFML/Graphics.hpp>
#include "../inc/Player.h"

Player::Player(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {
}

void Player::update(float deltaTime)
{
    Entity::update(deltaTime);
    gameplayInfo->setInfo<float>("playerHealth", entityCurrentHealth);
}






