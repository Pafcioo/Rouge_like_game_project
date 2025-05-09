#include "GameElement.h"

GameElement::GameElement(const std::string& label,
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    sf::Color color,   
    ShapeType type  
): UIElement(label), elementType_(type)
{
    if (elementType_ == ShapeType::Rectangle) {
        elementRect_.setPosition(position);
        elementRect_.setSize(size);
        elementRect_.setFillColor(color);
    } else if (elementType_ == ShapeType::Circle) {
        elementCircle_.setPosition(position);
        elementCircle_.setRadius(size.x / 2.f);
        elementCircle_.setFillColor(color);
    }
    // Dodaj obsługę ConvexShape jeśli potrzebujesz
}

void GameElement::setPosition(const sf::Vector2f& position) {
    if (elementType_ == ShapeType::Rectangle)
        elementRect_.setPosition(position);
    else if (elementType_ == ShapeType::Circle)
        elementCircle_.setPosition(position);
}

void GameElement::setSize(const sf::Vector2f& size) {
    if (elementType_ == ShapeType::Rectangle)
        elementRect_.setSize(size);
    else if (elementType_ == ShapeType::Circle)
        elementCircle_.setRadius(size.x / 2.f);
}

void GameElement::setColor(const sf::Color& color) {
    if (elementType_ == ShapeType::Rectangle)
        elementRect_.setFillColor(color);
    else if (elementType_ == ShapeType::Circle)
        elementCircle_.setFillColor(color);
}

void GameElement::setOutline(float thickness, sf::Color color) {
    if (elementType_ == ShapeType::Rectangle) {
        elementRect_.setOutlineThickness(thickness);
        elementRect_.setOutlineColor(color);
    } else if (elementType_ == ShapeType::Circle) {
        elementCircle_.setOutlineThickness(thickness);
        elementCircle_.setOutlineColor(color);
    }
}

void GameElement::update(float) {
    // Dodaj logikę jeśli potrzebujesz
}

void GameElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (elementType_ == ShapeType::Rectangle)
        target.draw(elementRect_, states);
    else if (elementType_ == ShapeType::Circle)
        target.draw(elementCircle_, states);
}