#include <SFML/Graphics.hpp>
#include "ItemBuilder.h"

void HealPotionBuilder::reset() {
    this->healPotion = std::make_shared<HealPotion>();
}

std::shared_ptr<Item> HealPotionBuilder::build() {
    this->reset();
    this->healPotion->setId(0);
    this->healPotion->setValue(50);
    this->healPotion->setName("Heal Potion");
    this->healPotion->setRarity(COMMON);
    return healPotion;
}



