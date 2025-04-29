#pragma once
#include <SFML/Graphics.hpp>

class Entity : sf::Drawable
{
    protected:
        int entityHealth;
        float entitySpeed;
        sf::Vector2f entityPosition;
        sf::Texture entityTexture;
        sf::Sprite entitySprite;
        bool entityCanMeleeAttack = true;
    public:
        Entity(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture): entityTexture(texture), entitySprite(entityTexture)
        {
            this->entityHealth = health;
            this->entitySpeed = speed;
            this->entityPosition = position;
        }
        ~Entity() override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void move(sf::Vector2f direction) = 0;
        virtual void attack() = 0;

};