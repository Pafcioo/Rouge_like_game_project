#include "../inc/Item.h"

void Item::setId(int id) {this->id = id;}
void Item::setName(std::string name) {this->name = name;}
void Item::setRarity(Rarity rarity) {this->rarity = rarity;}
void Item::setEffectAmount(float effectAmount) {this->effectAmount = effectAmount;}
void Item::setIsUsed(bool isUsed) {this->isUsed = isUsed;}
int Item::getId() {return id;}
std::string Item::getName() {return name;}
Rarity Item::getRarity() {return rarity;}
float Item::getEffectAmount() {return effectAmount;}
bool Item::getIsUsed() {return isUsed;}


