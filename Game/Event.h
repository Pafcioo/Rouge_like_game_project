#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <SFML/Graphics.hpp>

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
    using Handler = std::function<void(const EventType&)>; // action that will be triggered after receving a publish

    // Subscription of event, the handler(action) is added to map of handlers
    template<typename EventType>
    void subscribe(Handler<EventType> handler) {
        auto& handlers = handlers_[std::type_index(typeid(EventType))];
        handlers.push_back([handler](const EventBase& e) {
            handler(static_cast<const Event<EventType>&>(e).data);
        });
    }

    // Publication of event, after publishing every subscriber activate his action (handler)
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