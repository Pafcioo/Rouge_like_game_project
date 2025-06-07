#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <algorithm>

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

class SubscriptionHandle {
public:
    std::type_index type;
    size_t id;

    SubscriptionHandle(std::type_index type, size_t id) : type(type), id(id) {}
};


// Generic system for events
class EventBus {
public:
    template<typename EventType>
    using Handler = std::function<void(const EventType&)>;

    template<typename EventType>
    SubscriptionHandle subscribe(Handler<EventType> handler) {
        auto type = std::type_index(typeid(EventType));
        size_t id = nextId_++;

        handlers_[type].emplace_back(id, [handler](const EventBase& e) {
            handler(static_cast<const Event<EventType>&>(e).data);
        });

        return SubscriptionHandle(type, id);
    }

    void unsubscribe(const SubscriptionHandle& handle) {
        auto it = handlers_.find(handle.type);
        if (it != handlers_.end()) {
            auto& vec = it->second;
            vec.erase(std::remove_if(vec.begin(), vec.end(), [&](const auto& pair) {
                return pair.first == handle.id;
            }), vec.end());
        }
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
            for (auto& [id, handler] : it->second) {
                handler(e);
            }
        }
    }

private:
    size_t nextId_ = 0;
    std::unordered_map<std::type_index, std::vector<std::pair<size_t, std::function<void(const EventBase&)>>>> handlers_;
};

