#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "InputManager.h"
#include "UIElement.h"
#include "Event.h"
// Button inherits from UIElement so it can be in the same vector of UIElements
class Button : public UIElement {
public:
    // Pointer to function, there the action for button is stored
    using ClickAction = std::function<void()>;
    Button(
        const std::string& buttonLabel = "",
        sf::Vector2f buttonSize = sf::Vector2f(0.f, 0.f),
        sf::Vector2f buttonPosition,
        sf::Color buttonColor = sf::Color::White,
        std::string buttonTextString = "", 
        const sf::Font& buttonFont,
        unsigned int buttonCharacterSize = 1,
        ClickAction buttonClickAction,
        EventBus& eventBus  
    );
    // Setters
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setColor(const sf::Color& color);
    void setText(const std::string& text);
    void setTextColor(const sf::Color& color);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);

    // Getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::Color getColor() const;
    std::string getText() const;
    sf::Color getTextColor() const;
    unsigned int getCharacterSize() const;
    // Methods for hover effect of a button
    void setFocused(bool focused);
    bool isFocused() const;
    
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    bool focused_ = false;
    ClickAction onClick;
};