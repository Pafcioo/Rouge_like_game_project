#include "Button.h"
#include <iostream>

Button::Button(
    const std::string& buttonLabel = "",
    sf::Vector2f buttonSize = sf::Vector2f(0.f, 0.f),
    sf::Vector2f buttonPosition,
    sf::Color buttonColor = sf::Color::White,
    std::string buttonTextString = "", 
    const sf::Font& buttonFont,
    unsigned int buttonCharacterSize = 1,
    ClickAction buttonClickAction,
    EventBus& eventBus  
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
    eventBus.subscribe<MouseClickedEvent>([this](const MouseClickedEvent& mouseEvent){
        if(buttonShape.getGlobalBounds().contains(mouseEvent.positionOfClick)){
            if(onClick)
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
// Draw method for button
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonShape, states);
    target.draw(buttonText, states);
}
