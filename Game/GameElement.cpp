#include "GameElement.h"

GameElement::GameElement(ShapeType type, const sf::Vector2f& position, const sf::Vector2f& size , sf::Color color, const std::string& label)
    : UIElement(label), type_(type)
{
    if (type_ == ShapeType::Rectangle) {
        rect_.setPosition(position);
        rect_.setSize(size);
        rect_.setFillColor(color);
    } else if (type_ == ShapeType::Circle) {
        circle_.setPosition(position);
        circle_.setRadius(size.x / 2.f);
        circle_.setFillColor(color);
    }
    // Dodaj obsługę ConvexShape jeśli potrzebujesz
}

void GameElement::setPosition(const sf::Vector2f& position) {
    if (type_ == ShapeType::Rectangle)
        rect_.setPosition(position);
    else if (type_ == ShapeType::Circle)
        circle_.setPosition(position);
}

void GameElement::setSize(const sf::Vector2f& size) {
    if (type_ == ShapeType::Rectangle)
        rect_.setSize(size);
    else if (type_ == ShapeType::Circle)
        circle_.setRadius(size.x / 2.f);
}

void GameElement::setColor(const sf::Color& color) {
    if (type_ == ShapeType::Rectangle)
        rect_.setFillColor(color);
    else if (type_ == ShapeType::Circle)
        circle_.setFillColor(color);
}

void GameElement::setOutline(float thickness, sf::Color color) {
    if (type_ == ShapeType::Rectangle) {
        rect_.setOutlineThickness(thickness);
        rect_.setOutlineColor(color);
    } else if (type_ == ShapeType::Circle) {
        circle_.setOutlineThickness(thickness);
        circle_.setOutlineColor(color);
    }
}

void GameElement::update(float) {
    // Dodaj logikę jeśli potrzebujesz
}

void GameElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (type_ == ShapeType::Rectangle)
        target.draw(rect_, states);
    else if (type_ == ShapeType::Circle)
        target.draw(circle_, states);
}