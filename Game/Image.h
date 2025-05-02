#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class Image : public UIElement {
public:
    // Konstruktor ze skalą
    Image(const std::string& texturePath,
          const sf::Vector2f& position = {0.f, 0.f},
          const sf::Vector2f& scale = {1.f, 1.f},
          const sf::Angle& rotation = sf::degrees(0),
          const std::string& label = "");

    // Statyczna metoda fabrykująca z docelowym rozmiarem
    static std::shared_ptr<Image> createWithSize(
        const std::string& texturePath,
        const sf::Vector2f& position,
        const sf::Vector2f& targetSize,
        const sf::Angle& rotation = sf::degrees(0),
        const std::string& label = ""
    );

    void setPosition(const sf::Vector2f& position);
    void setTexture(const std::string& texturePath);
    void update(float deltaTime) override;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::string texturePath_;
};