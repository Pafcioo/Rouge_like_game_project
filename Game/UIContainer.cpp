#include <iostream>
#include "UIContainer.h"
#include "Text.h"
#include "Image.h"
#include "GameElement.h"

UIContainer::UIContainer(GameState overlayStateOfGame, EventBus& eventBus, bool canHaveBackgroundUI): eventBus_(eventBus){
    canHaveBackgroundUI_ = canHaveBackgroundUI;
    overlayStateOfGame_ = overlayStateOfGame;
}

int UIContainer::getFocusedIndex() const {
    return focusedIndex_;
}
// Setters and getters for background and active state
void UIContainer::setCanHaveBackgroundUI(bool value) {
    canHaveBackgroundUI_ = value;
}
bool UIContainer::canHaveBackgroundUI() const {
    return canHaveBackgroundUI_;
}
void UIContainer::setIsUIActive(bool value) {
    isUIActive_ = value;
}
bool UIContainer::isUIActive() const {
    return isUIActive_;
}
int UIContainer::getButtonCount() const {
    return static_cast<int>(uiElements_.size());
}

void UIContainer::focusNext() {
    if (uiElements_.empty()) return;
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get()))
            btn->setFocused(false);
    }
    for (int i = 1; i <= (int)uiElements_.size(); ++i) {
        int idx = (focusedIndex_ + i) % uiElements_.size();
        if (dynamic_cast<Button*>(uiElements_[idx].get())) {
            focusedIndex_ = idx;
            break;
        }
    }
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size() && uiElements_[focusedIndex_]) {
    if (auto* btn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get()))
        btn->setFocused(true);
    }
}

void UIContainer::focusPrevious() {
    if (uiElements_.empty()) return;
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get()))
            btn->setFocused(false);
    }
    for (int i = 1; i <= (int)uiElements_.size(); ++i) {
        int idx = (focusedIndex_ - i + uiElements_.size()) % uiElements_.size();
        if (dynamic_cast<Button*>(uiElements_[idx].get())) {
            focusedIndex_ = idx;
            break;
        }
    }
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size() && uiElements_[focusedIndex_]) {
    if (auto* btn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get()))
        btn->setFocused(true);
    }
}

void UIContainer::activateFocused() {
    if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
        if (auto* btn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get())) {
            if (btn->getClickAction()) {
                btn->getClickAction()(); // Wywołaj akcję kliknięcia
            }
        }
    }
}

void UIContainer::focusUIElement() {
    // Subskrybuj event kliknięcia myszy
    eventBus_.subscribe<sf::Event::MouseButtonPressed>([this](const sf::Event::MouseButtonPressed& event) {
        sf::Vector2f mousePosition(static_cast<float>(event.position.x), static_cast<float>(event.position.y));
        for (int i = 0; i < (int)uiElements_.size(); ++i) {
            if (auto* btn = dynamic_cast<Button*>(uiElements_[i].get())) {
                if (btn->getGlobalBoundsOfButton().contains(mousePosition)) {
                    activateFocused();
                }
            }
        }
    });

    // Subskrybuj event ruchu myszy (hover efekt)
    eventBus_.subscribe<sf::Event::MouseMoved>([this](const sf::Event::MouseMoved& event) {
        sf::Vector2f mousePosition(static_cast<float>(event.position.x), static_cast<float>(event.position.y));
        for (int i = 0; i < (int)uiElements_.size(); ++i) {
            if (auto* btn = dynamic_cast<Button*>(uiElements_[i].get())) {
                if (btn->getGlobalBoundsOfButton().contains(mousePosition)) {
                    if (focusedIndex_ != i) {
                        if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
                            if (auto* prevBtn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get())) {
                                prevBtn->setFocused(false);
                            }
                        }
                        btn->setFocused(true);
                        focusedIndex_ = i;
                    }
                    return;
                }
            }
        }
        // Unfocus if mouse is not over any button
        if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
            if (auto* prevBtn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get())) {
                prevBtn->setFocused(false);
            }
            focusedIndex_ = -1;
        }
    });

    eventBus_.subscribe<sf::Event::KeyPressed>([this](const sf::Event::KeyPressed& event){
        if(event.scancode == sf::Keyboard::Scancode::Up){
            focusPrevious();
        }
        if(event.scancode == sf::Keyboard::Scancode::Down){
            focusNext();
        }
        if(event.scancode == sf::Keyboard::Scancode::Enter){
            activateFocused();
        }
    });
}

void UIContainer::addElement(std::shared_ptr<UIElement> element) {
    if (uiElements_.empty()) {
        if (auto* btn = dynamic_cast<Button*>(element.get())) {
            btn->setFocused(true);
            focusedIndex_ = 0;
        }
    }
    uiElements_.push_back(std::move(element));
}

void UIContainer::drawAll(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& element : uiElements_) {
        element->draw(target, states);
    }
}
