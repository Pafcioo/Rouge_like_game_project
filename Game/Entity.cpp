#include "Entity.h"

float Entity::getEntitySpeed() {return entityCurrentSpeed;}
float Entity::getEntityBaseSpeed() {return entityBaseSpeed;}
void Entity::setSpeed(float newSpeed) {entityCurrentSpeed = newSpeed;}
void Entity::setHealth(float newHealth) {entityCurrentHealth = newHealth;}
float Entity::getHealth() {return entityCurrentHealth;}
sf::Vector2f Entity::getPosition() {return entityPosition;}
std::shared_ptr<Weapon> Entity::getWeapon() {return entityWeapon;}
