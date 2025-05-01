#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class Image : public UIElement {
public:
    Image(const std::string& texturePath, const sf::Vector2f& position = {0.f, 0.f}, const sf::Vector2f& scale = {1.f, 1.f});
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