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
    Button(std::shared_ptr<EventBus> eventBus,
        const std::string& buttonLabel = "",
        const sf::Vector2f& buttonSize = {0.f, 0.f},
        const sf::Vector2f& buttonPosition = {0.f, 0.f},
        sf::Color buttonColor = sf::Color::White,
        const std::string& buttonTextString = "",
        const sf::Font& buttonFont = sf::Font(),
        unsigned int buttonCharacterSize = 12,
        ClickAction buttonClickAction = nullptr,
        bool centerOrigin = false // New parameter
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
    sf::FloatRect getGlobalBoundsOfButton() const;
    ClickAction getClickAction(){
        return onClick;
    };
    // Methods for hover effect of a button
    void setFocused(bool focused);
    bool isFocused() const;
    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    bool focused_ = false;
    bool isActive = false;
    // Action triggered when clicking button
    ClickAction onClick;
    void setOriginCentered(bool centerOrigin);
};