#pragma once
#include <SFML/Graphics.hpp>

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
    float value;
public:
    Item() = default;
    virtual ~Item() = default;
    virtual void activate(Entity* entity) = 0;
    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setRarity(Rarity rarity) { this->rarity = rarity; }
    void setValue(float value) { this->value = value; }
    int getId() { return id; }
    std::string getName() { return name; }
    Rarity getRarity() { return rarity; }
    float getValue() { return value; }
};