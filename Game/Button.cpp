#include "Button.h"
#include <iostream>

Button::Button(
    EventBus& eventBus, 
    const std::string& buttonLabel,
    const sf::Vector2f& buttonSize,
    const sf::Vector2f& buttonPosition,
    sf::Color buttonColor,
    const std::string& buttonTextString, 
    const sf::Font& buttonFont,
    unsigned int buttonCharacterSize,
    ClickAction buttonClickAction
)
    : UIElement(buttonLabel), onClick(buttonClickAction), buttonText(buttonFont, buttonTextString, buttonCharacterSize)
{
    // All the essential atributes of a button are set here 
    buttonShape.setPosition(buttonPosition);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(buttonColor);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(buttonPosition);
    // Every button subscribe to mouse click event, so when mouse button is clicked the action is trigerred
    eventBus.subscribe<sf::Event::MouseButtonPressed>([this](const sf::Event::MouseButtonPressed& mouseEvent){
        if(buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseEvent.position))){
            if(onClick && isActive)
                onClick();
        };
    });
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
    // Add logic for updating the button if needed
    // For now, this can be left empty if no update logic is required.
}

// Draw method for button
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonShape, states);
    target.draw(buttonText, states);
}
