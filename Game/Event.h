#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

class GameState;

// Structures for custom events
struct PlayerDamagedEvent {
    int playerId;
    int damage;
};

struct MoveEvent {
    sf::Vector2f direction;
    float deltaTime;
};

struct AttackEvent {
    sf::Vector2f direction;
};

struct DashEvent {
    sf::Vector2f direction;
};

struct SpawnEvent {
    std::string labelOfSpawner;
};

struct ChangeStateEvent {
    std::shared_ptr<GameState> gameState;
};

struct RevertStateEvent {};

struct MapChoiceEvent {
    std::string mapLabel;
};

struct useAbilityEvent {};

// Base class for events, needed for storing pointers to this base class
class EventBase {
public:
    virtual ~EventBase() = default;
};

// Template event that stores any kind of event listed above in structures
template<typename T>
class Event : public EventBase {
public:
    T data;
    explicit Event(const T& data) : data(data) {}
};

// Generic system for events
class EventBus {
public:
    template<typename EventType>
    using Handler = std::function<void(const EventType&)>;

    template<typename EventType>
    void subscribe(Handler<EventType> handler) {
        auto& handlers = handlers_[std::type_index(typeid(EventType))];
        handlers.push_back([handler](const EventBase& e) {
            handler(static_cast<const Event<EventType>&>(e).data);
        });
    }

    template<typename EventType>
    void unsubscribeAll() {
        handlers_.erase(std::type_index(typeid(EventType)));
    }

    template<typename EventType>
    void publish(const EventType& event) {
        auto it = handlers_.find(std::type_index(typeid(EventType)));
        if (it != handlers_.end()) {
            Event<EventType> e(event);
            for (auto& handler : it->second) {
                handler(e);
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const EventBase&)>>> handlers_;
};
