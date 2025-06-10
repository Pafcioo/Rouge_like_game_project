#pragma once
#include <SFML/Graphics.hpp>
#include <any>

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
            if (!hasInfo(key)) {
                throw std::runtime_error("Key '" + key + "' not found in gameplayInfo.");
            }
            return std::any_cast<T>(gameplayInfo.at(key));
        }
        void setGameplayInfo(std::unordered_map<std::string, std::any> gameplayInfoSource);
        std::unordered_map<std::string, std::any> getGameplayInfo();
        bool hasInfo(const std::string& key) const;
};