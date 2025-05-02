#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class GameElement : public UIElement {
public:
    enum class ShapeType { Rectangle, Circle, Convex };

    GameElement(ShapeType type, const sf::Vector2f& position, const sf::Vector2f& size = {50.f, 50.f}, sf::Color color = sf::Color::White, const std::string& label = "");

    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setColor(const sf::Color& color);
    void setOutline(float thickness, sf::Color color);

    void update(float deltaTime) override;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ShapeType type_;
    sf::RectangleShape rect_;
    sf::CircleShape circle_;
    // Możesz dodać sf::ConvexShape convex_ jeśli chcesz obsłużyć niestandardowe kształty
};