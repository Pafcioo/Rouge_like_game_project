#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <SFML/Graphics.hpp>

struct PlayerDamagedEvent {
    int playerId;
    int damage;
};

struct MoveEvent {
    sf::Vector2f direction;
};

struct AttackEvent {
    sf::Vector2f direction;
};

struct DashEvent {
    sf::Vector2f direction;
};

struct MouseClickedEvent {
    sf::Vector2f positionOfClick;
};

// Bazowa klasa eventu (do przechowywania wskaźników)
class EventBase {
public:
    virtual ~EventBase() = default;
};

// Szablonowy event z danymi dowolnego typu
template<typename T>
class Event : public EventBase {
public:
    T data;
    explicit Event(const T& data) : data(data) {}
};

// EventBus - generyczny system eventów
class EventBus {
public:
    template<typename EventType>
    using Handler = std::function<void(const EventType&)>;

    // Subskrybuj event danego typu
    template<typename EventType>
    void subscribe(Handler<EventType> handler) {
        auto& handlers = handlers_[std::type_index(typeid(EventType))];
        handlers.push_back([handler](const EventBase& e) {
            handler(static_cast<const Event<EventType>&>(e).data);
        });
    }

    // Publikuj event danego typu
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