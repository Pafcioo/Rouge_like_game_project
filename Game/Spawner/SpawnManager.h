#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Spawner.h"
#include "SpawnStrategy.h"
#include "Game/Event.h"

class SpawnManager
{
    private:
        std::vector<std::shared_ptr<SpawnStrategy>> strategies;
    public:
        SpawnManager();
        ~SpawnManager() = default;
        void addStrategy(std::shared_ptr<SpawnStrategy> strategy);
        void update(float deltaTime);
};