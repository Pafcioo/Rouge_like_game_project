#include "../inc/Button.h"
#include <iostream>
#include <cmath>

Button::Button(
    std::shared_ptr<EventBus> eventBus, 
    const std::string& buttonLabel,
    const sf::Vector2f& buttonSize,
    const sf::Vector2f& buttonPosition,
    const sf::Color& buttonColor,
    const std::string& buttonTextString, 
    const sf::Font& buttonFont,
    unsigned int buttonCharacterSize,
    ClickAction buttonClickAction,
    bool centerOrigin
)
    : UIElement(buttonLabel), onClick(buttonClickAction), buttonText(buttonFont, buttonTextString, buttonCharacterSize)
{
    // Set button shape attributes
    buttonShape.setSize(buttonSize);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(buttonColor);
    buttonText.setFillColor(sf::Color::Black);
    setOriginCentered(centerOrigin);

    // Subscribe to mouse click event
    eventBus->subscribe<sf::Event::MouseButtonPressed>([this](const sf::Event::MouseButtonPressed& mouseEvent){
        if(buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseEvent.position))){
            if(onClick && isActive)
                onClick();
        };
    });
}

void Button::setOriginCentered(bool centerOrigin) {
    if (centerOrigin) {
        buttonShape.setOrigin({buttonShape.getSize().x / 2.f, buttonShape.getSize().y / 2.f});
    } else {
        buttonShape.setOrigin({0.f, 0.f});
    }
    buttonText.setOrigin(buttonText.getGlobalBounds().getCenter());
    buttonText.setPosition(buttonShape.getGlobalBounds().getCenter());
}

// This method is responsible for hover effect
void Button::setFocused(bool focused) {
    focused_ = focused;
    buttonShape.setOutlineThickness(focused ? 3.f : 0.f);
    buttonShape.setOutlineColor(sf::Color::Yellow);
}

// Down there there are basic setters and getters
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

bool Button::isFocused() const {
    return focused_;
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

sf::FloatRect Button::getGlobalBoundsOfButton() const {
    return buttonShape.getGlobalBounds();
}

void Button::update(float deltaTime) {
    
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonShape, states);
    target.draw(buttonText, states);
}
