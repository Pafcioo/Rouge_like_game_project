#include "Entity.h"
#include <cmath>
#include <iostream>

Entity::Entity(const float health, const float speed, const sf::Vector2f position, const sf::Texture &texture):
            entityTexture(texture), entitySprite(entityTexture)
{
    entityBaseHealth = health;
    entityCurrentHealth = health;
    entityBaseSpeed = speed;
    entityCurrentSpeed = speed;
    entityPosition = position;
    entityDirection = sf::Vector2f(1,0);
    entitySprite.setOrigin(static_cast<sf::Vector2f>(entityTexture.getSize())/2.f);
    entitySprite.setPosition(entityPosition);
    entitySprite.setColor(sf::Color::White);
    entitySprite.setScale({0.1, 0.1});
}

float Entity::getEntitySpeed() {
    return entityCurrentSpeed;
}

float Entity::getEntityBaseSpeed() {
    return entityBaseSpeed;
}

sf::Vector2f Entity::getEntityDirection() {
    return entityDirection;
}

void Entity::setEntityDirection(sf::Vector2f direction) {
    entityDirection = direction;
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

std::shared_ptr<Ability> Entity::getAbility() {
    return entityAbility;
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

sf::FloatRect Entity::getEntityGlobalBounds() {
    return entitySprite.getGlobalBounds();
}

void Entity::attack(sf::Vector2f direction)
{
    // Check if entity has a weapon equipped
    if (!entityWeapon) {
        return; // Cannot attack without a weapon
    }
    sf::Vector2f initialPosition;
    // Projectiles are shot outside player bounds, otherwise they would immediately deactivate
    initialPosition.x = (static_cast<float>(entityTexture.getSize().x)/2.f * entitySprite.getScale().x + 10);
    initialPosition.y = (static_cast<float>(entityTexture.getSize().y)/2.f * entitySprite.getScale().y + 10);
    
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
        initialPosition.x *= direction.x;
        initialPosition.x += entityPosition.x;
        initialPosition.y *= direction.y;
        initialPosition.y += entityPosition.y;
    }
    entityWeapon->shoot(initialPosition, direction, &typeid(*this));
}

void Entity::useItem(std::shared_ptr<Item> item)
{
    // Check if item exists
    if (!item) {
        return; // Cannot use null item
    }
    
    item->activate(this);
    item->setIsUsed(true);
}

void Entity::useAbility() 
{
    // Check if entity has an ability assigned
    if (!entityAbility) {
        return; // Cannot use ability if none is assigned
    }
    
    entityAbility->activate();
}

void Entity::update(float deltaTime) 
{
    // Update weapon if equipped
    if (entityWeapon) {
        entityWeapon->update(deltaTime);
    }
    
    // Update and apply ability effects if assigned
    if (entityAbility) {
        entityAbility->update(deltaTime);
        entityAbility->influence(this);
    }
}

void Entity::move(sf::Vector2f direction)
{
    this->entitySprite.move(direction * entityCurrentSpeed);
    entityPosition = entitySprite.getPosition();
    
    // Update gameplay info if available
    if (gameplayInfo) {
        gameplayInfo->setInfo<sf::Vector2f>("playerPos", entityPosition);
    }
}

