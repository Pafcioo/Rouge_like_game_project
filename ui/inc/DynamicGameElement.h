#pragma once
#include "GameElement.h"
#include "../../core/inc/GameplayInfoSource.h"
#include <functional>
#include <memory>

class DynamicGameElement : public GameElement {
public:
    // Constructor
    DynamicGameElement(
        std::function<void(std::shared_ptr<GameplayInfoSource>)> action,
        std::shared_ptr<GameplayInfoSource> infoSource,
        std::string label = "",
        const sf::Vector2f& size = {50.f, 50.f},
        const sf::Vector2f& position = {0.f, 0.f},
        sf::Color color = sf::Color::White,
        ShapeType type = ShapeType::Rectangle,
        bool centerOrigin = false
    );

    // Override update method to handle dynamic behavior
    void update(float deltaTime) override;

    // Size manipulation methods
    void setWidthPercentage(float percentage);  // 0.0f to 1.0f
    void setHeightPercentage(float percentage); // 0.0f to 1.0f
    void setOriginalSize(const sf::Vector2f& size);
    void resetSize();
    void setAction(std::function<void(std::shared_ptr<GameplayInfoSource>)> newAction) {
        action_ = newAction;
    }

    // Color and transparency control
    void setColor(const sf::Color& color);
    void setAlpha(uint8_t alpha);  // 0 = fully transparent, 255 = fully opaque
    void setColorWithAlpha(const sf::Color& color, uint8_t alpha);
    sf::Color getColor() const;

private:
    std::function<void(std::shared_ptr<GameplayInfoSource>)> action_;
    std::shared_ptr<GameplayInfoSource> infoSource_;
    sf::Vector2f originalSize_;
};