#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"

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
private:
    std::vector<std::shared_ptr<UIElement>> uiElements;
    int focusedIndex_ = -1;

};