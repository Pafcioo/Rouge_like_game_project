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
#include "Event.h"

class UIContainer
{
public:
    UIContainer(std::shared_ptr<EventBus> eventBus);
    ~UIContainer() = default;
    // Method for adding UIElements to UI(container)
    void addElement(std::shared_ptr<UIElement> element);
    // Methods for focusing functionality
    void focusNext();
    void focusPrevious();
    void activateFocused();
    void subscribeToEvents();
    int getFocusedIndex() const;
    int getButtonCount() const;
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
private:
    // Vector that stores pointers for UIElements
    std::vector<std::shared_ptr<UIElement>> uiElements_;
    // Reference to eventBus to control hover effect
    std::shared_ptr<EventBus> eventBus_;
    int focusedIndex_ = -1;
};