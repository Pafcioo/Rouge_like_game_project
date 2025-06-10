#include "../inc/AICooldown.h"
#include "../inc/AIController.h"

AICooldown::AICooldown(float cooldown)
{
    cooldownMulti = cooldown;
    timeSinceLastAction = 0.0f;
}

void AICooldown::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    auto attackComponent = aiController->getAttackComponent();
    timeSinceLastAction += deltaTime;
    if (timeSinceLastAction >= cooldownMulti) {
        if (attackComponent) {
            attackComponent->update(aiController);
        }
        timeSinceLastAction = 0.0f;
    }

}