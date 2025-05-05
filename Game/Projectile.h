#pragma once
#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable {
private:
    sf::Vector2f projectileInitialPosition;
    sf::Vector2f projectileVelocity;
    float projectileSpeed;
    bool projectileIsActive;
    sf::CircleShape projectileShape;
public:
    Projectile(sf::Vector2f position, sf::Vector2f velocity, float speed, float radius = 5.f, sf::Color color = sf::Color::White):
        projectileInitialPosition(position), projectileVelocity(velocity), projectileSpeed(speed), projectileIsActive(true) {
        projectileShape.setRadius(radius);
        projectileShape.setFillColor(color);
        projectileShape.setOrigin({radius, radius});
        projectileShape.setPosition(projectileInitialPosition);
    }
    ~Projectile() override = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(projectileShape, states);
    }
    void update(float deltaTime);
    bool isActive() const { return projectileIsActive; }
    void deactivate() { projectileIsActive = false; }
    sf::Vector2f getInitialPosition() const { return projectileInitialPosition; }
    sf::CircleShape getShape() const { return projectileShape; }
};