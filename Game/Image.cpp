#include "Image.h"
#include <iostream>

// Konstruktor ze skalą
Image::Image(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& scale, const sf::Angle& rotation)
    : texturePath_(texturePath), texture_(texturePath), sprite_(texture_)
{
    sprite_.setTexture(texture_);
    sprite_.setOrigin({texture_.getSize().x / 2.f, texture_.getSize().y / 2.f});
    sprite_.setScale(scale);
    sprite_.setPosition(position);
    sprite_.setRotation(rotation);
}

// Statyczna metoda fabrykująca z docelowym rozmiarem
std::shared_ptr<Image> Image::createWithSize(
    const std::string& texturePath,
    const sf::Vector2f& position,
    const sf::Vector2f& targetSize,
    const sf::Angle& rotation
) {
    auto img = std::make_shared<Image>(texturePath, position, sf::Vector2f(1.f, 1.f), rotation);
    img->sprite_.setScale(
        {targetSize.x / static_cast<float>(img->texture_.getSize().x),
        targetSize.y / static_cast<float>(img->texture_.getSize().y)}
    );
    return img;
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

void Image::update(float) {}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}