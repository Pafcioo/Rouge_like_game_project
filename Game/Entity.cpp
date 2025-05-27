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

float Entity::getEntitySpeed() {
    return entityCurrentSpeed;
}

float Entity::getEntityBaseSpeed() {
    return entityBaseSpeed;
}

void Entity::setSpeed(float newSpeed) {
    entityCurrentSpeed = newSpeed;
}

void Entity::setHealth(float newHealth) {
    entityCurrentHealth = newHealth;
}

float Entity::getHealth() {
    return entityCurrentHealth;
}

sf::Vector2f Entity::getPosition() {
    return entityPosition;
}

std::shared_ptr<Weapon> Entity::getWeapon() {
    return entityWeapon;
}

void Entity::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(entitySprite, states);
}

void Entity::setItem(std::shared_ptr<Item> item)
{
    entityItem = item;
}

void Entity::setAbility(std::shared_ptr<Ability> ability)
{
    entityAbility = ability;
}

void Entity::setWeapon(std::shared_ptr<Weapon> weapon)
{
    entityWeapon = weapon;
}
