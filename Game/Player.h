#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
    public:
    Player(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Player() override = default;
};