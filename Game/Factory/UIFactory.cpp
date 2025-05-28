#include "Game/Factory/UIFactory.h"

std::shared_ptr<UIContainer> MainMenuUI::createUI(std::shared_ptr<EventBus> eventBus)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    container->createUIElement<Text>(
        sf::Vector2f(100.f,30.f), //Position
        font,
        "Main Menu", //Text
        48, //Character size
        sf::Color::White, // Color of font
        "MainMenuTitle" // Label, used later for finding the element
    );
    container->createUIElement<Button>(
        eventBus, // event bus for subscribing and publishing events
        "PlayTheGameButton", //Label
        sf::Vector2f(100.f,50.f), // Position
        sf::Vector2f(100.f,100.f), // Size
        sf::Color::White, // Background color
        "Play", //Text
        font,
        24, //Character size
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<MapChoosing>()}); // Action to perform when button is clicked
        }
    );
    container->createUIElement<Button>(
        eventBus,
        "OptionsButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(100.f, 200.f),
        sf::Color::White,
        "Options",
        font,
        24,
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<Paused>()});
        }
    );
    container->createUIElement<Button>(
        eventBus,
        "MapChooseButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(100.f, 300.f),
        sf::Color::White,
        "Choose map",
        font,
        24,
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<MapChoosing>()});
        }
    );
    container->createUIElement<Button>(
        eventBus,
        "QuitButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(100.f, 400.f),
        sf::Color::White,
        "Quit",
        font,
        24,
        [](){
            
        }
    );
    container->createUIElement<Image>(
        "PlayerImage", //Label
        0.4, //Scale or target size(sf::Vector2f)
        sf::Vector2f(840.f,360.f), // Position
        sf::degrees(0), // Rotation
        "Assets/player.png" //Path to texture
    );
    return container;
}

std::shared_ptr<UIContainer> MapChoiceUI::createUI(std::shared_ptr<EventBus> eventBus)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    container->createUIElement<Button>(
        eventBus,
        "MapButton1",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(500.f, 360.f),
        sf::Color::White,
        "Desert Strike",
        font,
        24,
        [&](){
            eventBus->publish(MapChoiceEvent{"Desert Strike"});
            eventBus->publish(ChangeStateEvent{std::make_shared<InGame>()});
        },
        true
    );
    container->createUIElement<Button>(
        eventBus,
        "MapButton1",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(640.f, 360.f),
        sf::Color::White,
        "Forest Valley",
        font,
        24,
        [&](){
            eventBus->publish(MapChoiceEvent{"Forest Valley"});
            eventBus->publish(ChangeStateEvent{std::make_shared<InGame>()});
        },
        true
    );
    container->createUIElement<Button>(
        eventBus,
        "MapButton1",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(780.f, 360.f),
        sf::Color::White,
        "Castle",
        font,
        24,
        [&](){
            eventBus->publish(MapChoiceEvent{"Castle"});
            eventBus->publish(ChangeStateEvent{std::make_shared<InGame>()});
        },
        true
    );

    return container;
}

std::shared_ptr<UIContainer> InGameUI::createUI(std::shared_ptr<EventBus> eventBus)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    container->createUIElement<GameElement>(
        "EnergyBar",
        sf::Vector2f(300.f, 30.f),
        sf::Vector2f(50.f, 600.f),
        sf::Color::Red,
        ShapeType::Rectangle
    );
    container->createUIElement<GameElement>(
        "HealthBar",
        sf::Vector2f(300.f, 30.f),
        sf::Vector2f(50.f, 650.f),
        sf::Color::Red,
        ShapeType::Rectangle
    );
    container->createUIElement<Button>(
        eventBus,
        "OptionsButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(1100.f, 50.f),
        sf::Color::White,
        "Options",
        font,
        12,
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<Paused>()});
        }
    );

    return container;
}

std::shared_ptr<UIContainer> PauseUI::createUI(std::shared_ptr<EventBus> eventBus)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    container->createUIElement<GameElement>(
        "BackgroundOption", // Label
        sf::Vector2f(600,300), // Position
        sf::Vector2f(640,360), // Size
        sf::Color::Black, // Background color
        ShapeType::Rectangle, //Type of shape
        true // Centered origin
    );
    container->createUIElement<Button>(
        eventBus,
        "PlayTheGameButton",
        sf::Vector2f(100.f,100.f),
        sf::Vector2f(500.f,360.f),
        sf::Color::Green,
        "Play",
        font,
        12,
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<InGame>()});
        },
        true //Centered origin
    );
    container->createUIElement<Button>(
        eventBus,
        "OptionsButton",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(640.f, 360.f),
        sf::Color::Blue,
        "Go back",
        font,
        12,
        [&](){
            eventBus->publish(RevertStateEvent{}); // Revert to previous state
        },
        true
    );
    container->createUIElement<Button>(
        eventBus,
        "OptionsButton",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(780.f, 360.f),
        sf::Color::Blue,
        "Go back to main menu",
        font,
        12,
        [&](){
            eventBus->publish(ChangeStateEvent{std::make_shared<InMenu>()});
        },
        true
    );

    return container;
}