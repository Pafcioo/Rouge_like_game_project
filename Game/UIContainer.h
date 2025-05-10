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

enum class GameState;

class UIContainer
{
public:
    UIContainer(GameState overlayStateOfGame, EventBus& eventBus, sf::Clock& globalCooldownClock);
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
    // Setters and getters for background and active state
    void setCanHaveBackgroundUI(bool value);
    bool canHaveBackgroundUI() const;
    void setIsUIActive(bool value);
    bool isUIActive() const;
    // Generic method for creating UIElement
    template<typename TypeOfUIElement, typename... ArgsForUIElement>
    void createUIElement(ArgsForUIElement&&... args)
    {
        addElement(std::static_pointer_cast<UIElement>(
        std::make_shared<TypeOfUIElement>(std::forward<ArgsForUIElement>(args)...)
    ));
    }
    // Drawing method
    void drawAll(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    // Vector that stores pointers for UIElements
    std::vector<std::shared_ptr<UIElement>> uiElements_;
    // Reference to eventBus to control hover effect
    EventBus& eventBus_;
    // State of the game where the UI will be active and visible
    GameState overlayStateOfGame_;
    // Bool that decides whether the UI can have background UIs behind or not
    bool canHaveBackgroundUI_;
    // Bool that decides whether the UI is active/can be clicked and drawn
    bool isUIActive_ = true;
    int focusedIndex_ = -1;
    sf::Clock& globalCooldownClock_; // Reference to the global cooldown clock
};