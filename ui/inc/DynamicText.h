#pragma once
#include "Text.h"
#include "../../core/inc/GameplayInfoSource.h"
#include <functional>
#include <memory>

class DynamicText : public Text {
public:
    // Constructor
    DynamicText(
        std::function<void(std::shared_ptr<GameplayInfoSource>, DynamicText*)> action,
        std::shared_ptr<GameplayInfoSource> infoSource,
        const sf::Vector2f& position,
        const sf::Font& font,
        const std::string& initialText,
        unsigned int characterSize,
        sf::Color color,
        const std::string& label = "",
        bool centerText = false
    );

    // Override update method to handle dynamic behavior
    void update(float deltaTime) override;

    // Setter for action
    void setAction(std::function<void(std::shared_ptr<GameplayInfoSource>, DynamicText*)> newAction) {
        action_ = newAction;
    }

private:
    std::function<void(std::shared_ptr<GameplayInfoSource>, DynamicText*)> action_;
    std::shared_ptr<GameplayInfoSource> infoSource_;
};