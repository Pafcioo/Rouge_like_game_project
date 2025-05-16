#include <SFML/Graphics.hpp>
#include <any>

struct EnemyConfig {
    int health;
    float speed;
    sf::Vector2f position;
    sf::Texture* texture; // Use pointer to avoid copying
};

class GameplayInfoSource
{
    private:
        std::unordered_map<std::string, std::any> gameplayInfo;
    public:
        GameplayInfoSource() = default;
        ~GameplayInfoSource() = default;

        template<typename T>
        void setInfo(const std::string& key, const T& value)
        {
            gameplayInfo[key] = value;
        }

        template<typename T>
        T getInfo(const std::string& key) const
        {
            return std::any_cast<T>(gameplayInfo.at(key));
        }

        bool hasInfo(const std::string& key) const
        {
            return gameplayInfo.find(key) != gameplayInfo.end();
        }
};