#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

// Enum for different types of shapes
enum class ShapeType { 
    Rectangle,
    Circle,
    Convex 
};

class GameElement : public UIElement {
public:
    // Constructor
    GameElement(const std::string& label = "",
        const sf::Vector2f& size = {50.f, 50.f},
        const sf::Vector2f& position = {0.f, 0.f},
        sf::Color color = sf::Color::White,
        ShapeType type = ShapeType::Rectangle,
        bool centerOrigin = false // New parameter
    );
    // Setters
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setColor(const sf::Color& color);
    void setOutline(float thickness, sf::Color color);
    // Update method
    void update(float deltaTime) override;
    // Draw method
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ShapeType elementType_;
    sf::RectangleShape elementRect_;
    sf::CircleShape elementCircle_;
    void setOriginCentered(bool centerOrigin); // New private method
};