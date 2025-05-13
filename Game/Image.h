#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

class Image : public UIElement {
public:
    // Constructor with scale
    Image(const std::string& imageLabel = "",
          float imageScale = 1.f,
          const sf::Vector2f& imagePosition = {0.f, 0.f},
          const sf::Angle& imageRotation = sf::degrees(0),
          const std::string& imageTexturePath = "");
    // Constructor with target size of image
    Image(const std::string& imageLabel = "",
          const sf::Vector2f& imageTargetSize = {0.f, 0.f},
          const sf::Vector2f& imagePosition = {0.f, 0.f},
          const sf::Angle& imageRotation = sf::degrees(0),
          const std::string& imageTexturePath = "");
    // Setters
    void setPosition(const sf::Vector2f& position);
    void setTexture(const std::string& texturePath);
    // Update method
    void update(float deltaTime) override;
protected:
    // Drawing method
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    float imageScale_;
    std::shared_ptr<sf::Texture> imageTexture_;
    std::unique_ptr<sf::Sprite> imageSprite_;
    std::string imageTexturePath_;
};