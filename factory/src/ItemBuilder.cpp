#include "../inc/ItemBuilder.h"
#include "../../entity/inc/Potion.h"

void HealPotionBuilder::reset() {
    this->healPotion = std::make_shared<HealPotion>();
}

std::shared_ptr<Item> HealPotionBuilder::build() {
    this->reset();
    this->healPotion->setId(0);
    this->healPotion->setEffectAmount(50.f);
    this->healPotion->setName("Heal Potion");
    this->healPotion->setRarity(COMMON);
    return healPotion;
}