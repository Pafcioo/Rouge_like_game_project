#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

class Entity;

enum Rarity {
    COMMON,
    RARE,
    EPIC,
    LEGENDARY
};

class Item {
protected:
    int id;
    std::string name;
    Rarity rarity;
    float effectAmount;
    bool isUsed = false;
public:
    Item() = default;
    virtual ~Item() = default;
    virtual void activate(Entity* entity) = 0;
    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = std::move(name); }
    void setRarity(Rarity rarity) { this->rarity = rarity; }
    void setEffectAmount(float amount) { effectAmount = amount; }
    float getEffectAmount() { return effectAmount; }
    int getId() { return id; }
    std::string getName() { return name; }
    Rarity getRarity() { return rarity; }
    void setIsUsed(bool isUsed) { this->isUsed = isUsed; }
    bool getIsUsed() { return isUsed; }
};