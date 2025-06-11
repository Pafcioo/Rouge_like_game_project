#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class Text : public UIElement {
public:
    // Constructor for UIElement text
    Text(
        const sf::Vector2f positionOfText,
        const sf::Font& font, 
        const std::string& text, 
        unsigned int characterSize, 
        sf::Color color, 
        const std::string& label = "",
        bool centerText = false
    );
    // Setters
    void setPosition(const sf::Vector2f& position);
    void setString(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color& color);
    void setCentered(bool centered);
    // Getters
    sf::FloatRect getGlobalBounds() const;
    bool isCentered() const;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    void updatePosition();
    sf::Text text_;
    sf::Vector2f originalPosition_;
    unsigned int characterSize_;
    sf::Color color_;
    bool centerText_;
};