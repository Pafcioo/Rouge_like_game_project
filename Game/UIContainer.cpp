#include <iostream>
#include "UIContainer.h"

void UIContainer::addElement(std::unique_ptr<UIElement> element) {
    uiElements.push_back(std::move(element));
}

void UIContainer::drawAll(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& element : uiElements) {
        element->draw(target, states);
    }
}