#pragma once
#include <SFML/Graphics.hpp>
#include <typeindex>

class Projectile : public sf::Drawable {
private:
    sf::Vector2f projectileInitialPosition;
    sf::Vector2f projectileVelocity;
    float projectileSpeed;
    bool projectileIsActive;
    sf::CircleShape projectileShape;
    float projectileDamage;
    const std::type_index projectileType;
public:
    Projectile(sf::Vector2f position, sf::Vector2f velocity, float speed, float damage, std::type_index type, float radius = 5.f, sf::Color color = sf::Color::White);
    ~Projectile() override = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(float deltaTime);
    bool isActive() const;
    void deactivate();
    sf::Vector2f getInitialPosition() const;
    sf::CircleShape getShape() const;
    sf::FloatRect getGlobalBounds();
    float getDamage() const;
    std::type_index getProjectileType();
};