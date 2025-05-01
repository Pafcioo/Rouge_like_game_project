#include "Image.h"
#include <iostream>

Image::Image(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& scale)
    : texturePath_(texturePath), texture_(texturePath), sprite_(texture_)
{
    sprite_.setPosition(position);
    sprite_.setScale(scale);
}

void Image::setPosition(const sf::Vector2f& position) {
    sprite_.setPosition(position);
}

void Image::setTexture(const std::string& texturePath) {
    texturePath_ = texturePath;
    if (!texture_.loadFromFile(texturePath_)) {
        std::cerr << "Failed to load texture: " << texturePath_ << std::endl;
    }
    sprite_.setTexture(texture_);
}

void Image::update(float /*deltaTime*/) {
    // Brak logiki aktualizacji
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}