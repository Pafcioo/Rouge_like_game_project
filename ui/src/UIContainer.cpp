#include <iostream>
#include "UIContainer.h"
#include "Text.h"
#include "Image.h"
#include "GameElement.h"

// Constructor for UI container
UIContainer::UIContainer(std::shared_ptr<EventBus> eventBus) {
    eventBus_ = eventBus;
}

UIContainer::~UIContainer() {
    unsubscribeFromEvents();
}

void UIContainer::addElement(std::shared_ptr<UIElement> element) {
    uiElements_.push_back(std::move(element));
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
                btn->getClickAction()();
            }
        }
    }
}

void UIContainer::subscribeToEvents() {
    // Mouse Button Pressed
    subscriptionHandles_.push_back(eventBus_->subscribe<sf::Event::MouseButtonPressed>([this](const sf::Event::MouseButtonPressed& event) {
        if (!isUIActive_) return;
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
                    activateFocused();
                    return;
                }
            }
        }
    }));

    // Mouse Moved
    subscriptionHandles_.push_back(eventBus_->subscribe<sf::Event::MouseMoved>([this](const sf::Event::MouseMoved& event) {
        if (!isUIActive_) return;
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
        if (focusedIndex_ >= 0 && focusedIndex_ < (int)uiElements_.size()) {
            if (!isUIActive_) return;
            if (auto* prevBtn = dynamic_cast<Button*>(uiElements_[focusedIndex_].get())) {
                prevBtn->setFocused(false);
            }
            focusedIndex_ = -1;
        }
    }));

    // Key Pressed
    subscriptionHandles_.push_back(eventBus_->subscribe<sf::Event::KeyPressed>([this](const sf::Event::KeyPressed& event) {
        if (!isUIActive_) return;
        if (event.scancode == sf::Keyboard::Scancode::Up) {
            focusPrevious();
        }
        if (event.scancode == sf::Keyboard::Scancode::Down) {
            focusNext();
        }
        if (event.scancode == sf::Keyboard::Scancode::Enter) {
            activateFocused();
        }
    }));
}

void UIContainer::unsubscribeFromEvents() {
    for (const auto& handle : subscriptionHandles_) {
        eventBus_->unsubscribe(handle);
    }
    subscriptionHandles_.clear();
}

int UIContainer::getFocusedIndex() const {
    return focusedIndex_;
}

int UIContainer::getButtonCount() const {
    return static_cast<int>(std::count_if(uiElements_.begin(), uiElements_.end(), [](const auto& el) {
        return dynamic_cast<Button*>(el.get()) != nullptr;
    }));
}

void UIContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& el : uiElements_) {
        el->draw(target, states);
    }
}

void UIContainer::update(float deltaTime) {
    for (auto& el : uiElements_) {
        el->update(deltaTime);
    }
}
