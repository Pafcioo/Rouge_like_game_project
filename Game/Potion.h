#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"

class Potion : public Item {
public:
    Potion() = default;
    ~Potion() override = default;
    void activate(Entity* entity) override = 0;
};

class HealPotion : public Potion {
public:
    HealPotion() = default;
    ~HealPotion() override = default;
    void activate(Entity *entity) override;
};