#pragma once
#include <SFML/Graphics.hpp>
#include "Game/UI/UIContainer.h"

class UIFactory
{
    protected:
        sf::Font font;
    public:
        UIFactory();
        virtual ~UIFactory(){};
        virtual std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus) = 0;
};

class MainMenuUI : public UIFactory
{
    public:
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus);
};

class MapChoiceUI : public UIFactory
{
    public:
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus);
};

class InGameUI : public UIFactory
{
    public:
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus);
};

class PauseUI : public UIFactory
{
    public:
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus);
};

class GameOverUI : public UIFactory
{
    public:
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus);
};
