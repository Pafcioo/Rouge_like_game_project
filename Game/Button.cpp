#include "Button.h"
#include <iostream>

Button::Button(InputManager& inputManager, const sf::Vector2f& position, const sf::Font& font, const sf::Vector2f& size, const sf::Color& color, const std::string& text, unsigned int characterSize)
    : buttonText(font) // Initialize buttonText with text, font, and character size
{
    buttonShape.setPosition(position);
    buttonShape.setSize(size);
    buttonShape.setFillColor(color);

    buttonText.setString(text);
    buttonText.setCharacterSize(characterSize);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(position);

    inputManager.registerMousePressCallback(
        [this](const sf::Event& event) {
            if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(
                        static_cast<float>(mouseButtonPressed->position.x),
                        static_cast<float>(mouseButtonPressed->position.y)
                    );
                    if (buttonShape.getGlobalBounds().contains(mousePos)) {
                        if (onClick) onClick();
                    }
                }
            }
        }
    );
}

void Button::setPosition(const sf::Vector2f& position) {
    buttonShape.setPosition(position);
    buttonText.setPosition(position);
}

void Button::setSize(const sf::Vector2f& size) {
    buttonShape.setSize(size);
}

void Button::setColor(const sf::Color& color) {
    buttonShape.setFillColor(color);
}

void Button::setText(const std::string& text) {
    buttonText.setString(text);
}

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}

void Button::setFont(const sf::Font& font) {
    buttonText.setFont(font);
}

void Button::setCharacterSize(unsigned int size) {
    buttonText.setCharacterSize(size);
}

sf::Vector2f Button::getPosition() const {
    return buttonShape.getPosition();
}

sf::Vector2f Button::getSize() const {
    return buttonShape.getSize();
}

sf::Color Button::getColor() const {
    return buttonShape.getFillColor();
}

std::string Button::getText() const {
    return buttonText.getString();
}

sf::Color Button::getTextColor() const {
    return buttonText.getFillColor();
}

unsigned int Button::getCharacterSize() const {
    return buttonText.getCharacterSize();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonShape, states);
    target.draw(buttonText, states);
}

void Button::update(float /*deltaTime*/) {
    // Tu możesz dodać logikę aktualizacji przycisku (np. animacje, hover, itp.)
}