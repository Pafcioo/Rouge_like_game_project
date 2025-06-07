#pragma once
#include <SFML/Graphics.hpp>
#include "Game/UI/UIContainer.h"

class UIFactory
{
    public:
        UIFactory();
        virtual ~UIFactory() = default;
        virtual std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) = 0;
};

class MainMenuUI : public UIFactory
{
    public:
        MainMenuUI();
        ~MainMenuUI();
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) override;
};

class MapChoiceUI : public UIFactory
{
    public:
        MapChoiceUI();
        ~MapChoiceUI();
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) override;
};

class InGameUI : public UIFactory
{
    public:
        InGameUI();
        ~InGameUI();
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) override;
};

class PauseUI : public UIFactory
{
    public:
        PauseUI();
        ~PauseUI();
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) override;
};

class GameOverUI : public UIFactory
{
    public:
        GameOverUI();
        ~GameOverUI();
        std::shared_ptr<UIContainer> createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font) override;
};
