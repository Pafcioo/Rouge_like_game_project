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
    std::cout << "[DEBUG] Entity::attack() called with direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
    
    // Check if entity has a weapon equipped
    if (!entityWeapon) {
        std::cout << "[WARNING] Entity::attack() - No weapon equipped, attack cancelled" << std::endl;
        return; // Cannot attack without a weapon
    }
    
    std::cout << "[DEBUG] Entity position: (" << entityPosition.x << ", " << entityPosition.y << ")" << std::endl;
    std::cout << "[DEBUG] Entity texture size: " << entityTexture.getSize().x << "x" << entityTexture.getSize().y << std::endl;
    std::cout << "[DEBUG] Entity sprite scale: (" << entitySprite.getScale().x << ", " << entitySprite.getScale().y << ")" << std::endl;

    sf::Vector2f initialPosition;
    // Projectiles are shot outside player bounds, otherwise they would immediately deactivate
    initialPosition.x = entityPosition.x + (static_cast<float>(entityTexture.getSize().x)/2.f * entitySprite.getScale().x + 10) * direction.x;
    initialPosition.y = entityPosition.y + (static_cast<float>(entityTexture.getSize().y)/2.f * entitySprite.getScale().y + 10) * direction.y;
    
    std::cout << "[DEBUG] Calculated initial projectile position: (" << initialPosition.x << ", " << initialPosition.y << ")" << std::endl;
    
    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    std::cout << "[DEBUG] Direction vector magnitude: " << magnitude << std::endl;
    
    if (magnitude != 0.f) {
        direction /= magnitude; // Normalize the vector
        std::cout << "[DEBUG] Normalized direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
    } else {
        std::cout << "[WARNING] Direction vector has zero magnitude, using original direction" << std::endl;
    }
    
    std::cout << "[DEBUG] Calling weapon->shoot() with position: (" << initialPosition.x << ", " << initialPosition.y 
              << ") and direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
    
    entityWeapon->shoot(initialPosition, direction);
    
    std::cout << "[DEBUG] Entity::attack() completed successfully" << std::endl;
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

