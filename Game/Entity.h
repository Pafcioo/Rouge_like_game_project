#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Weapon.h"
#include "Game/GameplayInfoSource.h"
#include "Item.h"
#include "Potion.h"
#include "ItemBuilder.h"
#include "Ability.h"

class Entity : public sf::Drawable
{
    protected:
        float entityBaseHealth;
        float entityBaseSpeed;
        float entityCurrentHealth;
        float entityCurrentSpeed;
        sf::Vector2f entityPosition;
        sf::Texture entityTexture;
        sf::Sprite entitySprite;
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
        bool entityCanMeleeAttack = true;
        std::shared_ptr<Weapon> entityWeapon = std::make_shared<BasicWeapon>();
        std::shared_ptr<Item> entityItem;
        std::shared_ptr<Ability> entityAbility = std::make_shared<SprintAbility>();
    public:
        Entity(float health, float speed, sf::Vector2f position, const sf::Texture &texture);
        ~Entity() override = default;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(entitySprite, states);
        }
        float getEntitySpeed();
        float getEntityBaseSpeed();
        virtual void move(sf::Vector2f direction) = 0;
        virtual void attack(sf::Vector2f direction) = 0;
        virtual void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
        {
            gameplayInfo = gameplayInfoSource;
        }
        sf::Vector2f getPosition();
        std::shared_ptr<Weapon> getWeapon();
        virtual void useItem(std::shared_ptr<Item> item) = 0;
        virtual void useAbility() = 0;
        virtual void update(float deltaTime) = 0;
        float getHealth();
        void setHealth(float health);
        void setSpeed(float speed);
};