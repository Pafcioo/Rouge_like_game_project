#include "Button.h"
#include <iostream>

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, unsigned int characterSize, const sf::Font& font)
    : m_text(font), m_clicked(false) // Initialize m_text with text, font, and character size
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(color);

    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position);
}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    m_text.setPosition(position);
}

void Button::setSize(const sf::Vector2f& size) {
    m_shape.setSize(size);
}

void Button::setColor(const sf::Color& color) {
    m_shape.setFillColor(color);
}

void Button::setText(const std::string& text) {
    m_text.setString(text);
}

void Button::setTextColor(const sf::Color& color) {
    m_text.setFillColor(color);
}

void Button::setFont(const sf::Font& font) {
    m_text.setFont(font);
}

void Button::setCharacterSize(unsigned int size) {
    m_text.setCharacterSize(size);
}

sf::Vector2f Button::getPosition() const {
    return m_shape.getPosition();
}

sf::Vector2f Button::getSize() const {
    return m_shape.getSize();
}

sf::Color Button::getColor() const {
    return m_shape.getFillColor();
}

std::string Button::getText() const {
    return m_text.getString();
}

sf::Color Button::getTextColor() const {
    return m_text.getFillColor();
}

unsigned int Button::getCharacterSize() const {
    return m_text.getCharacterSize();
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    return m_shape.getGlobalBounds().contains(mousePos);
}

// void Button::handleEvent(const auto event, const sf::Vector2f& mousePos) {
//     if (event->is<sf::Event::MouseButtonPressed> &&
//         event->is<sf::Mouse::Button::Left> &&
//         isHovered(mousePos)) {
//         m_clicked = true;
//     }
// }

bool Button::wasClicked() const {
    return m_clicked;
}

void Button::resetClicked() {
    m_clicked = false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
    target.draw(m_text, states);
}