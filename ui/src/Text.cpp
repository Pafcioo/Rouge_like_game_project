#include <iostream>
#include "../inc/Text.h"

// Constructor for UIElement
Text::Text(
    const sf::Vector2f positionOfText,
    const sf::Font& font, 
    const std::string& text, 
    unsigned int characterSize, 
    sf::Color color, 
    const std::string& label,
    bool centerText
) 
    : UIElement(label),
    text_(font), 
    originalPosition_(positionOfText),
    characterSize_(characterSize), 
    color_(color),
    centerText_(centerText)
{
    text_.setString(text);
    text_.setCharacterSize(characterSize_);
    text_.setFillColor(color_);
    updatePosition();
}

// Setters
void Text::setPosition(const sf::Vector2f& position) {
    originalPosition_ = position;
    updatePosition();
}

void Text::setString(const std::string& text) {
    text_.setString(text);
    if (centerText_) {
        updatePosition(); // Recalculate position when text changes
    }
}

void Text::setCharacterSize(unsigned int size) {
    characterSize_ = size;
    text_.setCharacterSize(characterSize_);
    if (centerText_) {
        updatePosition(); // Recalculate position when size changes
    }
}

void Text::setColor(const sf::Color& color) {
    color_ = color;
    text_.setFillColor(color_);
}

void Text::setCentered(bool centered) {
    centerText_ = centered;
    updatePosition();
}

// Getters
sf::FloatRect Text::getGlobalBounds() const {
    return text_.getGlobalBounds();
}

bool Text::isCentered() const {
    return centerText_;
}

// Update method for text
void Text::update(float deltaTime) {
    // Add logic if needed
}

// Drawing method for text
void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text_, states);
}

// Private helper method to update position based on centering
void Text::updatePosition() {
    if (centerText_) {
        sf::FloatRect bounds = text_.getLocalBounds();
        sf::Vector2f centeredPosition = originalPosition_;
        centeredPosition.x -= bounds.size.x / 2.0f;
        centeredPosition.y -= bounds.size.y / 2.0f;
        text_.setPosition(centeredPosition);
    } else {
        text_.setPosition(originalPosition_);
    }
}