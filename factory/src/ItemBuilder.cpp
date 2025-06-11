#include "../inc/ItemBuilder.h"
#include "../../entity/inc/Potion.h"

void HealPotionBuilder::reset() {
    this->healPotion = std::make_shared<HealPotion>();
}

std::shared_ptr<Item> HealPotionBuilder::build(std::shared_ptr<GameplayInfoSource> info) {
    this->reset();
    this->healPotion->setId(0);
    this->healPotion->setEffectAmount(50.f);
    this->healPotion->setName("Heal Potion");
    this->healPotion->setRarity(COMMON);
    this->healPotion->setUseCounter(3);
    this->healPotion->setGameplayInfo(info);
    info->setInfo<int>("potionAmount",this->healPotion->getUseCounter());
    return healPotion;
}