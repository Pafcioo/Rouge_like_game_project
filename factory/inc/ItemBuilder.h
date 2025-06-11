#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../../entity/inc/Item.h"

class ItemBuilder {
public:
    ItemBuilder() = default;
    virtual ~ItemBuilder() = default;
    virtual void reset() = 0;
    virtual std::shared_ptr<Item> build(std::shared_ptr<GameplayInfoSource>) = 0;
};

class HealPotionBuilder : public ItemBuilder {
private:
    std::shared_ptr<Item> healPotion;
public:
    HealPotionBuilder() = default;
    ~HealPotionBuilder() override = default;
    void reset() override;
    std::shared_ptr<Item> build(std::shared_ptr<GameplayInfoSource>) override;
};