#include "Image.h"
#include <iostream>

// Constructor with scale
Image::Image(const std::string& imageLabel,
    const float imageScale,
    const sf::Vector2f& imagePosition,
    const sf::Angle& imageRotation,
    const std::string& imageTexturePath)
: UIElement(imageLabel),imageTexturePath_(imageTexturePath), imageTexture_(imageTexturePath), imageSprite_(imageTexture_)
{
    imageSprite_.setScale({imageScale,imageScale_});
    imageSprite_.setOrigin(imageSprite_.getGlobalBounds().getCenter());
    imageSprite_.setPosition(imagePosition);
    imageSprite_.setRotation(imageRotation);
}
// Constructor with target size of image
Image::Image(const std::string& imageLabel,
    const sf::Vector2f& imageTargetSize,
    const sf::Vector2f& imagePosition,
    const sf::Angle& imageRotation,
    const std::string& imageTexturePath)
: UIElement(imageLabel),imageTexturePath_(imageTexturePath), imageTexture_(imageTexturePath), imageSprite_(imageTexture_)
{
    // Compute the scale based on target size and size of texture
    sf::Vector2u textureSize = imageTexture_.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = imageTargetSize.x / static_cast<float>(textureSize.x);
        float scaleY = imageTargetSize.y / static_cast<float>(textureSize.y);
        imageSprite_.setScale({scaleX, scaleY});
    } 
    else {
        std::cerr << "Texture size is invalid for: " << imageTexturePath_ << std::endl;
    }
    imageSprite_.setOrigin(imageSprite_.getGlobalBounds().getCenter());
    imageSprite_.setPosition(imagePosition);
    imageSprite_.setRotation(imageRotation);
}


void Image::setPosition(const sf::Vector2f& position) {
    imageSprite_.setPosition(position);
}

void Image::setTexture(const std::string& texturePath) {
    imageTexturePath_ = texturePath;
    if (!imageTexture_.loadFromFile(imageTexturePath_)) {
        std::cerr << "Failed to load texture: " << imageTexturePath_ << std::endl;
    }
    imageSprite_.setTexture(imageTexture_);
}

void Image::update(float) {}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(imageSprite_, states);
}