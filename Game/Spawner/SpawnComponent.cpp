#include <iostream>
#include "Game/Spawner/SpawnComponent.h"

WeaponComponent::WeaponComponent(std::shared_ptr<Weapon> weapon)
    : weapon(weapon) {}

void WeaponComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->setWeapon(weapon);
}

void WeaponComponent::describe() const {
    std::cout << "WeaponComponent with weapon: " << weapon->getName() << "\n";
}

ItemComponent::ItemComponent(std::shared_ptr<Item> item)
    : item(item) {}

void ItemComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->addItem(item);
}

void ItemComponent::describe() const {
    std::cout << "ItemComponent with item: " << item->getName() << "\n";
}

AbilityComponent::AbilityComponent(std::shared_ptr<Ability> ability)
    : ability(ability) {}

void AbilityComponent::apply(std::shared_ptr<EntityBuilder> builder) const {
    builder->addAbility(ability);
}

void AbilityComponent::describe() const {
    std::cout << "AbilityComponent with ability: " << ability->getName() << "\n";
}