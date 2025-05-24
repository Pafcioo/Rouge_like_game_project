#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Weapon {
protected:
    float weaponFireCooldown;
    float timeSinceLastShot;
    std::string weaponName;
public:
    Weapon(float fireRate)
        : weaponFireCooldown(fireRate), timeSinceLastShot(0.f) {}
    virtual ~Weapon() = default;
    void shoot(sf::Vector2f position, sf::Vector2f velocity, float speed); //Shooting new projectiles
    void update(float deltaTime);
    std::string getWeaponName() {return weaponName;}
};

class BasicWeapon : public Weapon {
public:
    BasicWeapon(): Weapon(0.5f){weaponName = "Basic Weapon";}
    ~BasicWeapon() override = default;
};
