#include "../inc/GameElement.h"

// Default constructor
GameElement::GameElement(std::string label,
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    sf::Color color,   
    ShapeType type,
    bool centerOrigin
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
    setOriginCentered(centerOrigin);
}

// All the setters for GameElement object
void GameElement::setOriginCentered(bool centerOrigin) {
    if (centerOrigin) {
        if (elementType_ == ShapeType::Rectangle) {
            elementRect_.setOrigin({elementRect_.getSize().x / 2.f, elementRect_.getSize().y / 2.f});
        } else if (elementType_ == ShapeType::Circle) {
            elementCircle_.setOrigin({elementCircle_.getRadius(), elementCircle_.getRadius()});
        }
    } else {
        if (elementType_ == ShapeType::Rectangle) {
            elementRect_.setOrigin({0.f, 0.f});
        } else if (elementType_ == ShapeType::Circle) {
            elementCircle_.setOrigin({0.f, 0.f});
        }
    }
}

void GameElement::setPosition(const sf::Vector2f& position) {
    if (elementType_ == ShapeType::Rectangle)
        elementRect_.setPosition(position);
    else if (elementType_ == ShapeType::Circle)
        elementCircle_.setPosition(position);
}

void GameElement::setSize(const sf::Vector2f& size) {
    if (elementType_ == ShapeType::Rectangle) {
        elementRect_.setSize(size);
        setOriginCentered(elementRect_.getOrigin() != sf::Vector2f(0.f, 0.f)); // Update origin if centered
    } else if (elementType_ == ShapeType::Circle) {
        elementCircle_.setRadius(size.x / 2.f);
        setOriginCentered(elementCircle_.getOrigin() != sf::Vector2f(0.f, 0.f)); // Update origin if centered
    }
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
    // Add logic if needed
}

void GameElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (elementType_ == ShapeType::Rectangle)
        target.draw(elementRect_, states);
    else if (elementType_ == ShapeType::Circle)
        target.draw(elementCircle_, states);
}

sf::Vector2f GameElement::getSize() const {
    if (elementType_ == ShapeType::Rectangle) {
        return elementRect_.getSize();
    } else if (elementType_ == ShapeType::Circle) {
        float diameter = elementCircle_.getRadius() * 2.f;
        return sf::Vector2f(diameter, diameter);
    }
    return sf::Vector2f();
}

sf::Color GameElement::getColor() const {
    if (elementType_ == ShapeType::Rectangle)
        return elementRect_.getFillColor();
    else if (elementType_ == ShapeType::Circle)
        return elementCircle_.getFillColor();
    return sf::Color::White; // Default color if no shape is set
}