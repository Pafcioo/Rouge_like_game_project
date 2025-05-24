#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
    public:
    //Inventory playerInventory
    Player(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
        Entity(health, speed, position, texture) {
        entityWeapon = std::make_shared<BasicWeapon>();
    }
    ~Player() override = default;
    void move(sf::Vector2f direction) override;
    void attack(sf::Vector2f direction) override;
    void useItem(std::shared_ptr<Item> item) override;
    void useAbility() override;
};