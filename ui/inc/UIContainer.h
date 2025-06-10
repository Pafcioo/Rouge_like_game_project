#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "UIElement.h"
#include "Button.h"
#include "GameElement.h"
#include "Image.h"
#include "Text.h"
#include "../../core/inc/Event.h"

class UIContainer
{
public:
    UIContainer(std::shared_ptr<EventBus> eventBus);
    ~UIContainer();

    // Method for adding UIElements to UI(container)
    void addElement(std::shared_ptr<UIElement> element);

    // Methods for focusing functionality
    void focusNext();
    void focusPrevious();
    void activateFocused();

    void subscribeToEvents();
    void unsubscribeFromEvents();

    int getFocusedIndex() const;
    int getButtonCount() const;

    bool getIsUIActive() const { return isUIActive_; }
    void setIsUIActive(bool isUIActive) { isUIActive_ = isUIActive; }

    // Drawing method
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float deltaTime);

private:
    std::vector<std::shared_ptr<UIElement>> uiElements_;
    std::shared_ptr<EventBus> eventBus_;
    std::vector<SubscriptionHandle> subscriptionHandles_;
    int focusedIndex_ = -1;
    bool isUIActive_ = true;
};
