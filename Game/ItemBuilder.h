#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Potion.h"

class ItemBuilder {
public:
    ItemBuilder() = default;
    virtual ~ItemBuilder() = default;
    virtual void reset() = 0;
};

class HealPotionBuilder : public ItemBuilder {
private:
    std::shared_ptr<Potion> healPotion;
public:
    HealPotionBuilder() = default;
    ~HealPotionBuilder() override = default;
    void reset() override;
    std::shared_ptr<Potion> build();
};