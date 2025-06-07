#include "Game/Factory/UIFactory.h"
#include "Game/States/GameState.h"

UIFactory::UIFactory(){}

// Constructors
MainMenuUI::MainMenuUI() : UIFactory() {}
MapChoiceUI::MapChoiceUI() : UIFactory() {}
InGameUI::InGameUI() : UIFactory() {}
PauseUI::PauseUI() : UIFactory() {}
GameOverUI::GameOverUI() : UIFactory() {}

// Destructors
MainMenuUI::~MainMenuUI() = default;
MapChoiceUI::~MapChoiceUI() = default;
InGameUI::~InGameUI() = default;
PauseUI::~PauseUI() = default;
GameOverUI::~GameOverUI() = default;

std::shared_ptr<UIContainer> MainMenuUI::createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    container->createUIElement<Text>(
        sf::Vector2f(100.f,30.f),
        font,
        "Main Menu",
        48,
        sf::Color::White,
        "MainMenuTitle"
    );

    container->createUIElement<Button>(
        eventBus,
        "PlayTheGameButton",
        sf::Vector2f(100.f,50.f),
        sf::Vector2f(100.f,100.f),
        sf::Color::White,
        "Play",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<MapChoosing>()}); }
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
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<Paused>()}); }
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
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<MapChoosing>()}); }
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
        [weakBus](){ if (auto bus = weakBus.lock()) {/* bus->publish(QuitGameEvent{}); */} }
    );

    container->createUIElement<Image>(
        "PlayerImage",
        0.4,
        sf::Vector2f(840.f,360.f),
        sf::degrees(0),
        "Assets/player.png"
    );

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> MapChoiceUI::createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    container->createUIElement<Button>(
        eventBus,
        "MapButton1",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(500.f, 360.f),
        sf::Color::White,
        "Desert Strike",
        font,
        24,
        [weakBus](){
            if (auto bus = weakBus.lock()) {
                bus->publish(MapChoiceEvent{"Desert Strike"});
                bus->publish(ChangeStateEvent{std::make_shared<InGame>()});
            }
        },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "MapButton2",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(640.f, 360.f),
        sf::Color::White,
        "Forest Valley",
        font,
        24,
        [weakBus](){
            if (auto bus = weakBus.lock()) {
                bus->publish(MapChoiceEvent{"Forest Valley"});
                bus->publish(ChangeStateEvent{std::make_shared<InGame>()});
            }
        },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "MapButton3",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(780.f, 360.f),
        sf::Color::White,
        "Castle",
        font,
        24,
        [weakBus](){
            if (auto bus = weakBus.lock()) {
                bus->publish(MapChoiceEvent{"Castle"});
                bus->publish(ChangeStateEvent{std::make_shared<InGame>()});
            }
        },
        true
    );

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> InGameUI::createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    container->createUIElement<GameElement>("EnergyBar", sf::Vector2f(300.f, 30.f), sf::Vector2f(50.f, 600.f), sf::Color::Red, ShapeType::Rectangle);
    container->createUIElement<GameElement>("HealthBar", sf::Vector2f(300.f, 30.f), sf::Vector2f(50.f, 650.f), sf::Color::Red, ShapeType::Rectangle);

    container->createUIElement<Button>(
        eventBus,
        "OptionsButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(1100.f, 50.f),
        sf::Color::White,
        "Options",
        font,
        12,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<Paused>()}); }
    );

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> PauseUI::createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    container->createUIElement<GameElement>("BackgroundOption", sf::Vector2f(600,300), sf::Vector2f(640,360), sf::Color::Black, ShapeType::Rectangle, true);

    container->createUIElement<Button>(
        eventBus,
        "PlayTheGameButton",
        sf::Vector2f(100.f,100.f),
        sf::Vector2f(500.f,360.f),
        sf::Color::Green,
        "Play",
        font,
        12,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<InGame>()}); },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "GoBackButton",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(640.f, 360.f),
        sf::Color::Blue,
        "Go back",
        font,
        12,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(RevertStateEvent{}); },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "GoBackToMenuButton",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(780.f, 360.f),
        sf::Color::Blue,
        "Go back to main menu",
        font,
        12,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<InMenu>()}); },
        true
    );

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> GameOverUI::createUI(std::shared_ptr<EventBus> eventBus, sf::Font& font)
{
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    container->createUIElement<GameElement>("GameOverBackground", sf::Vector2f(800, 600), sf::Vector2f(640, 360), sf::Color(0, 0, 0, 128), ShapeType::Rectangle, true);

    container->createUIElement<Text>(sf::Vector2f(640.f, 200.f), font, "GAME OVER", 64, sf::Color::Red, "GameOverTitle");

    container->createUIElement<Button>(
        eventBus,
        "PlayAgainButton",
        sf::Vector2f(200.f, 60.f),
        sf::Vector2f(540.f, 320.f),
        sf::Color::Green,
        "Play Again",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<MapChoosing>()}); },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "MainMenuButton",
        sf::Vector2f(200.f, 60.f),
        sf::Vector2f(740.f, 320.f),
        sf::Color::Blue,
        "Main Menu",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(ChangeStateEvent{std::make_shared<InMenu>()}); },
        true
    );

    container->createUIElement<Button>(
        eventBus,
        "QuitGameButton",
        sf::Vector2f(200.f, 60.f),
        sf::Vector2f(640.f, 400.f),
        sf::Color::Red,
        "Quit Game",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) {/* bus->publish(QuitGameEvent{}); */} },
        true
    );

    container->subscribeToEvents();
    return container;
}
