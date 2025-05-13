#include "Image.h"
#include <iostream>

// Constructor with scale
Image::Image(const std::string& imageLabel,
    const float imageScale,
    const sf::Vector2f& imagePosition,
    const sf::Angle& imageRotation,
    const std::string& imageTexturePath)
: UIElement(imageLabel), imageTexturePath_(imageTexturePath),
  imageTexture_(std::make_shared<sf::Texture>()) // Initialize shared_ptr
{
    if (!imageTexture_->loadFromFile(imageTexturePath_)) {
        std::cerr << "Failed to load texture: " << imageTexturePath_ << std::endl;
        return;
    }
    imageSprite_ = std::make_unique<sf::Sprite>(*imageTexture_); // Initialize unique_ptr with texture
    
    imageSprite_->setOrigin({imageSprite_->getGlobalBounds().size.x / 2.f,
                            imageSprite_->getGlobalBounds().size.y / 2.f});
    imageSprite_->setScale({imageScale, imageScale});
    imageSprite_->setPosition(imagePosition);
    imageSprite_->setRotation(imageRotation);
}

// Constructor with target size of image
Image::Image(const std::string& imageLabel,
    const sf::Vector2f& imageTargetSize,
    const sf::Vector2f& imagePosition,
    const sf::Angle& imageRotation,
    const std::string& imageTexturePath)
: UIElement(imageLabel), imageTexturePath_(imageTexturePath),
  imageTexture_(std::make_shared<sf::Texture>()) // Initialize shared_ptr
{
    if (!imageTexture_->loadFromFile(imageTexturePath_)) {
        std::cerr << "Failed to load texture: " << imageTexturePath_ << std::endl;
        return;
    }
    imageSprite_ = std::make_unique<sf::Sprite>(*imageTexture_); // Initialize unique_ptr with texture
    sf::Vector2u textureSize = imageTexture_->getSize();
    imageSprite_->setOrigin({imageSprite_->getGlobalBounds().size.x / 2.f,
                            imageSprite_->getGlobalBounds().size.y / 2.f});
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = imageTargetSize.x / static_cast<float>(textureSize.x);
        float scaleY = imageTargetSize.y / static_cast<float>(textureSize.y);
        imageSprite_->setScale({scaleX, scaleY});
    } else {
        std::cerr << "Texture size is invalid for: " << imageTexturePath_ << std::endl;
    }
    imageSprite_->setPosition(imagePosition);
    imageSprite_->setRotation(imageRotation);
}

void Image::setPosition(const sf::Vector2f& position) {
    if (imageSprite_) {
        imageSprite_->setPosition(position);
    }
}

void Image::setTexture(const std::string& texturePath) {
    imageTexturePath_ = texturePath;
    if (!imageTexture_->loadFromFile(imageTexturePath_)) {
        std::cerr << "Failed to load texture: " << imageTexturePath_ << std::endl;
        return;
    }
    imageSprite_->setTexture(*imageTexture_);
}

void Image::update(float) {}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (imageSprite_) {
        target.draw(*imageSprite_, states);
    }
}