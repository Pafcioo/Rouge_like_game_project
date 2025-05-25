#include <SFML/Graphics.hpp>
#include "Game/Factory/EntityBuilder.h"

class SpawnComponent {
public:
    virtual ~SpawnComponent() = default;

    virtual void apply(std::shared_ptr<EntityBuilder> builder) const = 0;
    virtual void describe() const = 0;
};

// class WeaponComponent : public SpawnComponent {
//     std::shared_ptr<Weapon> weapon;
// public:
//     WeaponComponent(std::shared_ptr<Weapon> weapon);

//     void apply(std::shared_ptr<EntityBuilder> builder) const override;
//     void describe() const override;
// };

// class ItemComponent : public SpawnComponent {
//     std::shared_ptr<Item> item;
// public:
//     ItemComponent(std::shared_ptr<Item> item);

//     void apply(std::shared_ptr<EntityBuilder> builder) const override;
//     void describe() const override;
// };

// class AbilityComponent : public SpawnComponent {
//     std::shared_ptr<Ability> ability;
// public:
//     AbilityComponent(std::shared_ptr<Ability> ability);

//     void apply(std::shared_ptr<EntityBuilder> builder) const override;
//     void describe() const override;
// };

class DifficultyComponent : public SpawnComponent {
    std::shared_ptr<AIControllerDifficulty> difficultyComponent;
public:
    DifficultyComponent(std::shared_ptr<AIControllerDifficulty> difficulty);

    void apply(std::shared_ptr<EntityBuilder> builder) const override;
    void describe() const override;
};