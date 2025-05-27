#include "Entity.h"

Entity::Entity(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            entityTexture(texture), entitySprite(entityTexture)
{
    entityBaseHealth = health;
    entityCurrentHealth = health;
    entityBaseSpeed = speed;
    entityCurrentSpeed = speed;
    entityPosition = position;
    entitySprite.setOrigin(static_cast<sf::Vector2f>(entityTexture.getSize())/2.f);
    entitySprite.setPosition(entityPosition);
    entitySprite.setColor(sf::Color::White);
    entitySprite.setScale({0.1, 0.1});
    ItemBuilder* builder = new HealPotionBuilder();
    entityItem = builder->build();
    delete builder;

}

float Entity::getEntitySpeed() {return entityCurrentSpeed;}
float Entity::getEntityBaseSpeed() {return entityBaseSpeed;}
void Entity::setSpeed(float newSpeed) {entityCurrentSpeed = newSpeed;}
void Entity::setHealth(float newHealth) {entityCurrentHealth = newHealth;}
float Entity::getHealth() {return entityCurrentHealth;}
sf::Vector2f Entity::getPosition() {return entityPosition;}
std::shared_ptr<Weapon> Entity::getWeapon() {return entityWeapon;}
