#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Item.h"
#include "Potion.h"
#include "ItemBuilder.h"
#include "Ability.h"

class Entity : public sf::Drawable
{
    protected:
        float entityBaseHealth;
        float entityBaseSpeed;
        float entityCurrentHealth = entityBaseHealth;
        float entityCurrentSpeed = entityBaseSpeed;
        sf::Vector2f entityPosition;
        sf::Texture entityTexture;
        sf::Sprite entitySprite;
        bool entityCanMeleeAttack = true;
        std::shared_ptr<Weapon> entityWeapon;
        std::shared_ptr<Item> entityItem;
        std::shared_ptr<Ability> entityAbility = std::make_shared<SprintAbility>();
    public:
        Entity(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            entityTexture(texture), entitySprite(entityTexture)
        {
            entityBaseHealth = health;
            entityBaseSpeed = speed;
            entityPosition = position;
            entitySprite.setOrigin(static_cast<sf::Vector2f>(entityTexture.getSize())/2.f);
            entitySprite.setPosition(entityPosition);
            entitySprite.setColor(sf::Color::White);
            entitySprite.setScale({0.1, 0.1});
            ItemBuilder* builder = new HealPotionBuilder();
            entityItem = builder->build();
            delete builder;

        }
        ~Entity() override = default;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(entitySprite, states);
        }
        float getEntitySpeed() {return entityCurrentSpeed;}
        float getEntityBaseSpeed() {return entityBaseSpeed;}
        virtual void move(sf::Vector2f direction) = 0;
        virtual void attack(sf::Vector2f direction) = 0;
        sf::Vector2f getPosition() const { return entityPosition; }
        std::shared_ptr<Weapon> getWeapon() {return entityWeapon;}
        virtual void useItem(std::shared_ptr<Item> item) = 0;
        virtual void useAbility() = 0;
        float getHealth() const { return entityCurrentHealth; }
        void setHealth(float health) { entityCurrentHealth = health; }
        void setSpeed(float speed) { entityCurrentSpeed = speed; }
};