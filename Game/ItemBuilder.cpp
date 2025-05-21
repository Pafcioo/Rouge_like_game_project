#include <SFML/Graphics.hpp>
#include "ItemBuilder.h"

void HealPotionBuilder::reset() {
    this->healPotion = std::make_shared<HealPotion>();
}

std::shared_ptr<Potion> HealPotionBuilder::build() {
    this->reset();
    this->healPotion->setId(0);
    this->healPotion->setEffectAmount(50.f);
    this->healPotion->setName("Heal Potion");
    this->healPotion->setRarity(COMMON);
    return healPotion;
}



