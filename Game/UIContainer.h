#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Button.h"

class InputManager;

class UIContainer
{
public:
    UIContainer() = default;
    ~UIContainer() = default;

    void addElement(std::shared_ptr<UIElement> element);

    void drawAll(sf::RenderTarget& target, sf::RenderStates states) const;

    void focusNext();
    void focusPrevious();
    void activateFocused();
    void focusByMouse(const sf::Vector2f& mousePos);
    int getFocusedIndex() const { return focusedIndex_; }
    int getButtonCount() const { return static_cast<int>(uiElements.size()); }

    void createButton(
        InputManager& inputManager,
        const sf::Vector2f& position,
        const sf::Font& font,
        const std::string& text,
        Button::ClickAction onClick,
        Button::IsVisiblePredicate isVisible,
        const sf::Vector2f& size = {200.f, 50.f},
        const sf::Color& color = sf::Color::White,
        unsigned int characterSize = 24
    );

    void createText(
        const sf::Font& font,
        const std::string& text,
        const sf::Vector2f& position,
        unsigned int characterSize = 30,
        sf::Color color = sf::Color::White
    );

    void createImage(
        const std::string& texturePath,
        const sf::Vector2f& position = {0.f, 0.f},
        const sf::Vector2f& scale = {1.f, 1.f}
    );

private:
    std::vector<std::shared_ptr<UIElement>> uiElements;
    int focusedIndex_ = -1;

};