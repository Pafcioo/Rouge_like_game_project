#include <sstream>
#include "../inc/UIFactory.h"
#include "../../core/inc/GameState.h"
#include "../../ui/inc/DynamicGameElement.h"
#include "../../ui/inc/DynamicText.h"

UIFactory::UIFactory(){}

// Constructors
MainMenuUI::MainMenuUI() : UIFactory() {}
MapChoiceUI::MapChoiceUI() : UIFactory() {}
InGameUI::InGameUI() : UIFactory() {}
PauseUI::PauseUI() : UIFactory() {}
GameOverUI::GameOverUI() : UIFactory() {}

std::shared_ptr<UIContainer> MainMenuUI::createUI(
    std::shared_ptr<EventBus> eventBus, 
    sf::Font& font,
    std::shared_ptr<GameplayInfoSource> gameplayInfo
) {
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    // Title
    auto titleText = std::make_shared<Text>(
        sf::Vector2f(100.f,30.f),
        font,
        "Main Menu",
        48,
        sf::Color::White,
        "MainMenuTitle"
    );
    container->addElement(titleText);

    // Play button
    auto playButton = std::make_shared<Button>(
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
    container->addElement(playButton);

    // Options button
    auto optionsButton = std::make_shared<Button>(
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
    container->addElement(optionsButton);

    // Map choice button
    auto mapChoiceButton = std::make_shared<Button>(
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
    container->addElement(mapChoiceButton);

    // Quit button
    auto quitButton = std::make_shared<Button>(
        eventBus,
        "QuitButton",
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(100.f, 400.f),
        sf::Color::White,
        "Quit",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) {bus->publish(QuitGameEvent{});} }
    );
    container->addElement(quitButton);

    // Player image
    auto playerImage = std::make_shared<Image>(
        "PlayerImage",
        0.4,
        sf::Vector2f(840.f,360.f),
        sf::degrees(0),
        "resources/images/player.png"
    );
    container->addElement(playerImage);

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> MapChoiceUI::createUI(
    std::shared_ptr<EventBus> eventBus, 
    sf::Font& font,
    std::shared_ptr<GameplayInfoSource> gameplayInfo
) {
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    // Desert Strike button
    auto desertButton = std::make_shared<Button>(
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
    container->addElement(desertButton);

    // Forest Valley button
    auto forestButton = std::make_shared<Button>(
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
    container->addElement(forestButton);

    // Castle button
    auto castleButton = std::make_shared<Button>(
        eventBus,
        "MapButton3",
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(780.f, 360.f),
        sf::Color::White,
        "Parking",
        font,
        24,
        [weakBus](){
            if (auto bus = weakBus.lock()) {
                bus->publish(MapChoiceEvent{"Parking"});
                bus->publish(ChangeStateEvent{std::make_shared<InGame>()});
            }
        },
        true
    );
    container->addElement(castleButton);

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> InGameUI::createUI(
    std::shared_ptr<EventBus> eventBus, 
    sf::Font& font,
    std::shared_ptr<GameplayInfoSource> gameplayInfo
) {
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    // Create health bar
    auto healthBar = std::make_shared<DynamicGameElement>(
        nullptr,
        gameplayInfo,
        "HealthBar",
        sf::Vector2f(300.f, 30.f),
        sf::Vector2f(50.f, 650.f),
        sf::Color::Red,
        ShapeType::Rectangle
    );
    
    healthBar->setAction([healthBar](std::shared_ptr<GameplayInfoSource> info) {
        if (info->hasInfo("playerHealth") && info->hasInfo("playerInitialHealth")) {
            float health = info->getInfo<float>("playerHealth");
            float maxHealth = info->getInfo<float>("playerInitialHealth");
            float percentage = health / maxHealth;
            healthBar->setWidthPercentage(percentage);
        }
    });
    container->addElement(healthBar);

    // Create energy bar (modified to show ability cooldown)
    auto energyBar = std::make_shared<DynamicGameElement>(
        nullptr,
        gameplayInfo,
        "EnergyBar",
        sf::Vector2f(300.f, 30.f),
        sf::Vector2f(50.f, 600.f),
        sf::Color::Blue,
        ShapeType::Rectangle
    );
    
    energyBar->setAction([energyBar](std::shared_ptr<GameplayInfoSource> info) {
        if (info->hasInfo("playerAbilityCooldown") && info->hasInfo("playerAbilityMaxCooldown")) {
            float currentCooldown = info->getInfo<float>("playerAbilityCooldown");
            float maxCooldown = info->getInfo<float>("playerAbilityMaxCooldown");
            // Invert the percentage since we want the bar to fill up as cooldown decreases
            float percentage = 1.0f - (currentCooldown / maxCooldown);
            energyBar->setWidthPercentage(percentage);
            
            // Make the bar more transparent while regenerating
            if (percentage < 1.0f) {
                energyBar->setAlpha(128); // Semi-transparent
            } else {
                energyBar->setAlpha(255); // Fully opaque when ready
            }
        }
    });
    container->addElement(energyBar);

    // Create options button
    auto optionsButton = std::make_shared<Button>(
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
    container->addElement(optionsButton);

    auto gameTimer = std::make_shared<DynamicText>(
    [](std::shared_ptr<GameplayInfoSource> info, DynamicText* text) {
        if (info->hasInfo("gameTime")) {
            float totalSeconds = info->getInfo<float>("gameTime");
            int minutes = static_cast<int>(totalSeconds) / 60;
            int seconds = static_cast<int>(totalSeconds) % 60;
            
            std::stringstream ss;
            ss << "Time: " << std::setfill('0') << std::setw(2) << minutes 
               << ":" << std::setfill('0') << std::setw(2) << seconds;
            
            text->setString(ss.str());
        }
    },
    gameplayInfo,
    sf::Vector2f(1100.f, 20.f),  // Position in top-right corner
    font,
    "Time: 00:00",  // Initial text
    24,             // Font size
    sf::Color::White,
    "GameTimer",
    false           // Not centered
    );

    container->addElement(gameTimer);

    auto potionCounter = std::make_shared<DynamicText>(
    [](std::shared_ptr<GameplayInfoSource> info, DynamicText* text) {
        if (info->hasInfo("potionAmount")) {
            int potions = info->getInfo<int>("potionAmount");
            std::stringstream ss;
            ss << "Potions: " << potions;
            text->setString(ss.str());
        }
    },
    gameplayInfo,
    sf::Vector2f(50.f, 550.f),  // Position below timer
    font,
    "Potions: 0",    // Initial text
    24,              // Font size
    sf::Color::White,
    "PotionCounter",
    false            // Not centered
);

    container->addElement(potionCounter);

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> PauseUI::createUI(
    std::shared_ptr<EventBus> eventBus, 
    sf::Font& font,
    std::shared_ptr<GameplayInfoSource> gameplayInfo
) {
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    // Background
    auto background = std::make_shared<GameElement>(
        "BackgroundOption", 
        sf::Vector2f(600,300), 
        sf::Vector2f(640,360), 
        sf::Color::Black, 
        ShapeType::Rectangle, 
        true
    );
    container->addElement(background);

    // Play button
    auto playButton = std::make_shared<Button>(
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
    container->addElement(playButton);

    // Back button
    auto backButton = std::make_shared<Button>(
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
    container->addElement(backButton);

    // Main menu button
    auto menuButton = std::make_shared<Button>(
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
    container->addElement(menuButton);

    container->subscribeToEvents();
    return container;
}

std::shared_ptr<UIContainer> GameOverUI::createUI(
    std::shared_ptr<EventBus> eventBus, 
    sf::Font& font,
    std::shared_ptr<GameplayInfoSource> gameplayInfo
) {
    auto container = std::make_shared<UIContainer>(eventBus);
    std::weak_ptr<EventBus> weakBus = eventBus;

    // Background
    auto background = std::make_shared<GameElement>(
        "GameOverBackground", 
        sf::Vector2f(800, 600), 
        sf::Vector2f(640, 360), 
        sf::Color(0, 0, 0, 128), 
        ShapeType::Rectangle, 
        true
    );
    container->addElement(background);

    // Game Over text
    auto gameOverText = std::make_shared<Text>(
        sf::Vector2f(640.f, 200.f), 
        font, 
        "GAME OVER", 
        64, 
        sf::Color::Red, 
        "GameOverTitle", 
        true
    );
    container->addElement(gameOverText);

    // Play Again button
    auto playAgainButton = std::make_shared<Button>(
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
    container->addElement(playAgainButton);

    // Main Menu button
    auto mainMenuButton = std::make_shared<Button>(
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
    container->addElement(mainMenuButton);

    // Quit Game button
    auto quitButton = std::make_shared<Button>(
        eventBus,
        "QuitGameButton",
        sf::Vector2f(200.f, 60.f),
        sf::Vector2f(640.f, 400.f),
        sf::Color::Red,
        "Quit Game",
        font,
        24,
        [weakBus](){ if (auto bus = weakBus.lock()) bus->publish(QuitGameEvent{}); },
        true
    );
    container->addElement(quitButton);

    container->subscribeToEvents();
    return container;
}
