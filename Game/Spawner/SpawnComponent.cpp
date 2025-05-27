#include <iostream>
#include "Game/Spawner/SpawnComponent.h"

// WeaponComponent::WeaponComponent(std::shared_ptr<Weapon> weapon)
//     : weapon(weapon) {}

void WeaponComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->setWeapon();
}

void WeaponComponent::describe() const {
    std::cout << "WeaponComponent with weapon: " << weapon->getWeaponName() << "\n";
}

// ItemComponent::ItemComponent(std::shared_ptr<Item> item)
//     : item(item) {}

void ItemComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->setItem();
}
>>>>>>> main

// void ItemComponent::describe() const {
//     std::cout << "ItemComponent with item: " << item->getName() << "\n";
// }

// AbilityComponent::AbilityComponent(std::shared_ptr<Ability> ability)
//     : ability(ability) {}

// void AbilityComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
//     builder->setAbility(ability);
// }

// void AbilityComponent::describe() const {
//     std::cout << "AbilityComponent with ability: " << ability->getName() << "\n";
// }

DifficultyComponent::DifficultyComponent(std::shared_ptr<AIControllerDifficulty> difficulty)
    : difficultyComponent(difficulty) {}

void DifficultyComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->setDifficulty(difficultyComponent);
}

void DifficultyComponent::describe() const {
    std::cout << "Difficulty";

void AbilityComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->setAbility();
}

void AbilityComponent::describe() const {
    std::cout << "AbilityComponent with ability: " << ability->getAbilityName() << "\n";
}