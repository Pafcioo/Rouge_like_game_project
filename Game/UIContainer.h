#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"

class UIContainer
{
public:
    UIContainer() = default;
    ~UIContainer() = default;

    void addElement(std::unique_ptr<UIElement> element);

    void drawAll(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::vector<std::unique_ptr<UIElement>> uiElements;

};