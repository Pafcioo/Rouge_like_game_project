#include <iostream>
#include "UIContainer.h"
#include "Button.h"

void UIContainer::focusNext() {
    if (uiElements.empty()) return;
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
            btn->setFocused(false);
    }
    for (int i = 1; i <= (int)uiElements.size(); ++i) {
        int idx = (focusedIndex_ + i) % uiElements.size();
        if (dynamic_cast<Button*>(uiElements[idx].get())) {
            focusedIndex_ = idx;
            break;
        }
    }
    if (auto* btn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
        btn->setFocused(true);
}

void UIContainer::focusPrevious() {
    if (uiElements.empty()) return;
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
            btn->setFocused(false);
    }
    for (int i = 1; i <= (int)uiElements.size(); ++i) {
        int idx = (focusedIndex_ - i + uiElements.size()) % uiElements.size();
        if (dynamic_cast<Button*>(uiElements[idx].get())) {
            focusedIndex_ = idx;
            break;
        }
    }
    if (auto* btn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
        btn->setFocused(true);
}

void UIContainer::activateFocused() {
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements[focusedIndex_].get())) {
            if (btn->onClick) btn->onClick();
        }
    }
}

void UIContainer::addElement(std::unique_ptr<UIElement> element) {
    if (uiElements.empty()) {
        if (auto* btn = dynamic_cast<Button*>(element.get())) {
            btn->setFocused(true);
            focusedIndex_ = 0;
        }
    }
    uiElements.push_back(std::move(element));
}

void UIContainer::drawAll(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& element : uiElements) {
        element->draw(target, states);
    }
}

void UIContainer::focusByMouse(const sf::Vector2f& mousePos) {
    for (int i = 0; i < (int)uiElements.size(); ++i) {
        if (auto* btn = dynamic_cast<Button*>(uiElements[i].get())) {
            if (btn->getGlobalBounds().contains(mousePos)) {
                if (focusedIndex_ != i) {
                    // Unfocus previous
                    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements.size()) {
                        if (auto* prevBtn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
                            prevBtn->setFocused(false);
                    }
                    btn->setFocused(true);
                    focusedIndex_ = i;
                }
                return;
            }
        }
    }
    // Unfocus if mouse is not over any button
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements.size()) {
        if (auto* prevBtn = dynamic_cast<Button*>(uiElements[focusedIndex_].get()))
            prevBtn->setFocused(false);
        focusedIndex_ = -1;
    }
}