#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
    public:
    //Inventory playerInventory
    Player(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Player() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
    void useItem(std::shared_ptr<Item> item) override;
    void useAbility() override;
    void update(float deltaTime) override;
};