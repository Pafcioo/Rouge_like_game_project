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
    void setId(int id);
    void setName(std::string name);
    void setRarity(Rarity rarity);
    void setEffectAmount(float amount);
    float getEffectAmount();
    int getId();
    std::string getName();
    Rarity getRarity();
    void setIsUsed(bool isUsed);
    bool getIsUsed();
};