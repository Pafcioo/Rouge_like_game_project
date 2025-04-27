#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button : public sf::Drawable {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, unsigned int characterSize, const sf::Font& font);

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

    // Hover and click
    bool isHovered(const sf::Vector2f& mousePos) const;
    //void handleEvent(const auto event, const sf::Vector2f& mousePos);
    bool wasClicked() const;
    void resetClicked();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    bool m_clicked = false;
};