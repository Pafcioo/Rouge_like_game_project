#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Weapon.h"
#include "Game/GameplayInfoSource.h"
#include "Item.h"
#include "Potion.h"
#include "ItemBuilder.h"
#include "Ability.h"

// Abstract base class for all game entities
class Entity : public sf::Drawable
{
protected:
    // Core stats
    float entityBaseHealth;
    float entityBaseSpeed;
    float entityCurrentHealth;
    float entityCurrentSpeed;
    
    // Position & movement
    sf::Vector2f entityPosition;
    sf::Vector2f entityDirection;
    
    // Rendering
    sf::Texture entityTexture;
    sf::Sprite entitySprite;
    
    // Game systems
    std::shared_ptr<GameplayInfoSource> gameplayInfo;
    bool entityCanMeleeAttack = true;
    
    // Equipment
    std::shared_ptr<Weapon> entityWeapon;
    std::shared_ptr<Item> entityItem;
    std::shared_ptr<Ability> entityAbility;

public:
    Entity(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
    ~Entity() override = default;

    // Rendering
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // Getters
    float getEntitySpeed();
    float getEntityBaseSpeed();
    sf::Vector2f getEntityDirection();
    sf::Vector2f getPosition();
    sf::FloatRect getEntityGlobalBounds();
    float getHealth();
    std::shared_ptr<Weapon> getWeapon();
    std::shared_ptr<Ability> getAbility();

    // Setters
    void setEntityDirection(sf::Vector2f direction);
    void setHealth(float health);
    void setSpeed(float speed);
    void setItem(std::shared_ptr<Item> item);
    void setAbility(std::shared_ptr<Ability> ability);
    void setWeapon(std::shared_ptr<Weapon> weapon);
    virtual void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource);

    // Actions
    virtual void move(sf::Vector2f direction);
    virtual void attack(sf::Vector2f direction);
    virtual void useItem(std::shared_ptr<Item> item);
    virtual void useAbility();
    virtual void update(float deltaTime);
};