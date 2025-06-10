#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include <memory>

class ItemBuilder {
public:
    ItemBuilder() = default;
    virtual ~ItemBuilder() = default;
    virtual void reset() = 0;
    virtual std::shared_ptr<Item> build() = 0;
};

class HealPotionBuilder : public ItemBuilder {
private:
    std::shared_ptr<Item> healPotion;
public:
    HealPotionBuilder() = default;
    ~HealPotionBuilder() override = default;
    void reset() override;
    std::shared_ptr<Item> build() override;
};