#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "InputManager.h"
#include "UIElement.h"

class Button : public UIElement {
public:

    using ClickAction = std::function<void()>;
    using IsVisiblePredicate = std::function<bool()>;
    Button(InputManager& inputManager, 
        const sf::Vector2f& position, 
        const sf::Font& font,
        const sf::Vector2f& size={0.f,0.f},
        const sf::Color& color=sf::Color::White,
        const std::string& text="",
        unsigned int characterSize=1,
        IsVisiblePredicate isVisible = []() { return true; });
    
    
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
    sf::FloatRect getGlobalBounds() const { return buttonShape.getGlobalBounds(); }

    void setCallback(ClickAction action) {
        onClick = std::move(action);
    }

    void setFocused(bool focused);
    bool isFocused() const;

    void update(float deltaTime) override;
    ClickAction onClick;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    IsVisiblePredicate isVisible_;
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    bool focused_ = false;
};