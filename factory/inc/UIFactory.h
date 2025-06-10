#pragma once
#include <SFML/Graphics.hpp>
#include "../../ui/inc/UIContainer.h"
#include "../../core/inc/GameplayInfoSource.h"

class UIFactory
{
    public:
        UIFactory();
        virtual ~UIFactory() = default;
        virtual std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) = 0;
};

class MainMenuUI : public UIFactory
{
    public:
        MainMenuUI();
        ~MainMenuUI() = default;
        std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) override;
};

class MapChoiceUI : public UIFactory
{
    public:
        MapChoiceUI();
        ~MapChoiceUI() = default;
        std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) override;
};

class InGameUI : public UIFactory
{
    public:
        InGameUI();
        ~InGameUI() = default;
        std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) override;
};

class PauseUI : public UIFactory
{
    public:
        PauseUI();
        ~PauseUI() = default;
        std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) override;
};

class GameOverUI : public UIFactory
{
    public:
        GameOverUI();
        ~GameOverUI() = default;
        std::shared_ptr<UIContainer> createUI(
            std::shared_ptr<EventBus> eventBus, 
            sf::Font& font,
            std::shared_ptr<GameplayInfoSource> gameplayInfo = nullptr
        ) override;
};
