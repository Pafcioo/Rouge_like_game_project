#include <iostream>
#include "Text.h"
// Constructor for UIElement 
Text::Text(
    const sf::Vector2f positionOfText,
    const sf::Font& font, 
    const std::string& text, 
    unsigned int characterSize, 
    sf::Color color, 
    const std::string& label
)
    : UIElement(label),
    text_(font), 
    characterSize_(characterSize), 
    color_(color) 
{
    text_.setPosition(positionOfText);
    text_.setString(text);
    text_.setCharacterSize(characterSize_);
    text_.setFillColor(color_);
}
//Setters
void Text::setPosition(const sf::Vector2f& position) {
    text_.setPosition(position);
}

void Text::setString(const std::string& text) {
    text_.setString(text);
}

void Text::setCharacterSize(unsigned int size) {
    characterSize_ = size;
    text_.setCharacterSize(characterSize_);
}

void Text::setColor(const sf::Color& color) {
    color_ = color;
    text_.setFillColor(color_);
}
// Getters
sf::FloatRect Text::getGlobalBounds() const {
    return text_.getGlobalBounds();
}
// Update method for text
void Text::update(float deltaTime) {
    // Add logic if needed
}
// Drawing method for text
void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text_, states);
}

