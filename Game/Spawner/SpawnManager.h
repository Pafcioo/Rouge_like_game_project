#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Spawner.h"
#include "Game/Event.h"

class SpawnManager
{
    private:
        std::vector<std::shared_ptr<AbstractSpawner>> spawners;
        std::shared_ptr<EventBus> eventBus;
    public:
        SpawnManager(std::shared_ptr<EventBus> eventBus) : eventBus(eventBus) {};
        ~SpawnManager() = default;
        void addSpawner(std::shared_ptr<AbstractSpawner> spawner)
        {
            spawners.push_back(spawner);
        }
        void update(float deltaTime)
        {
            for (auto& spawner : spawners)
            {
                spawner->update(deltaTime);
            }
        }

};