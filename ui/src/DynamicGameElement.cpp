#include "DynamicGameElement.h"
#include <algorithm>

DynamicGameElement::DynamicGameElement(
    std::function<void(std::shared_ptr<GameplayInfoSource>)> action,
    std::shared_ptr<GameplayInfoSource> infoSource,
    std::string label,
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    sf::Color color,
    ShapeType type,
    bool centerOrigin
)
    : GameElement(label, size, position, color, type, centerOrigin)
    , action_(action)
    , infoSource_(infoSource)
{
    originalSize_ = size;
}

void DynamicGameElement::update(float deltaTime)
{
    GameElement::update(deltaTime);
    if (action_ && infoSource_) {
        action_(infoSource_);
    }
}

void DynamicGameElement::setWidthPercentage(float percentage)
{
    percentage = std::clamp(percentage, 0.0f, 1.0f);
    auto currentSize = getSize();
    setSize({originalSize_.x * percentage, currentSize.y});
}

void DynamicGameElement::setHeightPercentage(float percentage)
{
    percentage = std::clamp(percentage, 0.0f, 1.0f);
    auto currentSize = getSize();
    setSize({currentSize.x, originalSize_.y * percentage});
}

void DynamicGameElement::setOriginalSize(const sf::Vector2f& size)
{
    originalSize_ = size;
}

void DynamicGameElement::resetSize()
{
    setSize(originalSize_);
}

void DynamicGameElement::setColor(const sf::Color& color) {
    GameElement::setColor(color);
}

void DynamicGameElement::setAlpha(uint8_t alpha) {
    sf::Color currentColor = getColor();
    currentColor.a = alpha;
    setColor(currentColor);
}

void DynamicGameElement::setColorWithAlpha(const sf::Color& color, uint8_t alpha) {
    sf::Color newColor = color;
    newColor.a = alpha;
    setColor(newColor);
}

sf::Color DynamicGameElement::getColor() const {
    return GameElement::getColor();
}