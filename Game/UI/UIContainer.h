#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Game/UI/UIElement.h"
#include "Game/UI/Button.h"
#include "Game/UI/GameElement.h"
#include "Game/UI/Image.h"
#include "Game/UI/Text.h"
#include "Game/Event.h"

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

    // Generic method for creating UIElement
    template<typename TypeOfUIElement, typename... ArgsForUIElement>
    void createUIElement(ArgsForUIElement&&... args)
    {
        addElement(std::static_pointer_cast<UIElement>(
            std::make_shared<TypeOfUIElement>(std::forward<ArgsForUIElement>(args)...)
        ));
    }

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
