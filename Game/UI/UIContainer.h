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
    void unsubscribeFromEvents(); // New method

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
    // Vector that stores pointers for UIElements
    std::vector<std::shared_ptr<UIElement>> uiElements_;

    // Reference to eventBus to control hover effect
    std::shared_ptr<EventBus> eventBus_;

    // Store callback IDs for unsubscribing
    std::vector<std::size_t> subscriptionHandles_; // New member

    // Index of currently focused element
    int focusedIndex_ = -1;
    bool isUIActive_ = true; // Flag to check if UI is active
};
