#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include "../../logic/inc/ProjectileManager.h"

class Weapon {
protected:
    float weaponFireCooldown;
    float timeSinceLastShot;
    std::string weaponName;
    float projSpeed;
    float projDamage;
public:
    Weapon(float fireRate);
    virtual ~Weapon() = default;
    virtual void shoot(sf::Vector2f position, sf::Vector2f velocity, std::type_index type) = 0; 
    void update(float deltaTime);
    std::string getWeaponName();
};

class BasicWeapon : public Weapon {
public:
    BasicWeapon();
    ~BasicWeapon() override = default;
    void shoot(sf::Vector2f position, sf::Vector2f velocity, std::type_index type) override;
};
