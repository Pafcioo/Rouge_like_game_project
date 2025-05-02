#include <iostream>
#include "Text.h"

Text::Text(const sf::Font& font, const std::string& text, unsigned int characterSize, sf::Color color, const std::string& label)
    : UIElement(label), font_(font), text_(font), characterSize_(characterSize), color_(color) {
    text_.setString(text);
    text_.setCharacterSize(characterSize_);
    text_.setFillColor(color_);
}

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

void Text::setFont(const sf::Font& font) {
    font_ = font;
    text_.setFont(font_);
}

void Text::update(float /*deltaTime*/) {
    // Jeśli nie potrzebujesz aktualizacji, zostaw puste ciało
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text_, states);
}

