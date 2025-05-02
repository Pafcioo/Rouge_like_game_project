#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class Text : public UIElement {

public:
    Text(const sf::Font& font, const std::string& text, unsigned int characterSize, sf::Color color, const std::string& label = "");
    void setPosition(const sf::Vector2f& position);
    void setString(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color& color);
    void setFont(const sf::Font& font);

    sf::FloatRect getGlobalBounds() const { return text_.getGlobalBounds(); }
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Text text_;
    sf::Font font_;
    unsigned int characterSize_;
    sf::Color color_;
};