#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"

class Entity : public sf::Drawable
{
    protected:
        int entityHealth;
        float entitySpeed;
        sf::Vector2f entityPosition;
        sf::Vector2f entityDirection = {1.f, 0.f};
        sf::Texture entityTexture;
        sf::Sprite entitySprite;
        bool entityCanMeleeAttack = true;
        Weapon gun;
    public:
        Entity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            entityTexture(texture), entitySprite(entityTexture)
        {
            entityHealth = health;
            entitySpeed = speed;
            entityPosition = position;
            entitySprite.setOrigin(static_cast<sf::Vector2f>(entityTexture.getSize())/2.f);
            entitySprite.setPosition(entityPosition);
            entitySprite.setColor(sf::Color::White);
            entitySprite.setScale({0.1, 0.1});
        }
        ~Entity() override = default;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(entitySprite, states);
        }
        virtual float getEntitySpeed() = 0;
        virtual void move(sf::Vector2f direction) = 0;
        virtual void attack(sf::Vector2f direction) = 0;
        sf::Vector2f getEntityPosition() const { return entityPosition; }
        sf::Vector2f getEntityDirection() const { return entityDirection; }
        void setEntityDirection(sf::Vector2f direction) { entityDirection = direction; }
        sf::FloatRect getEntityGlobalBounds() const { return entitySprite.getGlobalBounds(); }
        Weapon* getWeapon() {return &gun;}
};