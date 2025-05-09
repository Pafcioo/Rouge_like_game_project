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
        const std::string& label = ""
    );
    // Setters
    void setPosition(const sf::Vector2f& position);
    void setString(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color& color);
    // Getters
    sf::FloatRect getGlobalBounds() const;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Text text_;
    unsigned int characterSize_;
    sf::Color color_;
};