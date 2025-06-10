#include "../inc/DynamicText.h"
#include <iomanip>
#include <sstream>

DynamicText::DynamicText(
    std::function<void(std::shared_ptr<GameplayInfoSource>, DynamicText*)> action,
    std::shared_ptr<GameplayInfoSource> infoSource,
    const sf::Vector2f& position,
    const sf::Font& font,
    const std::string& initialText,
    unsigned int characterSize,
    sf::Color color,
    const std::string& label,
    bool centerText
)
    : Text(position, font, initialText, characterSize, color, label, centerText)
    , action_(action)
    , infoSource_(infoSource)
{
}

void DynamicText::update(float deltaTime)
{
    Text::update(deltaTime);
    if (action_ && infoSource_) {
        action_(infoSource_, this);
    }
}