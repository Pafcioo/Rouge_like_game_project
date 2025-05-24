#pragma once
#include <memory>

class AbstractAIController;

class AbstractAISensing
{
    public:
        virtual ~AbstractAISensing() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class VisionSensing : public AbstractAISensing
{
    private:
        float visionRange;
        float attackRange;
        bool isEntityVisible;
        bool isInRangeToAttack;
    public:
        VisionSensing(float vision, float attack);
        ~VisionSensing() = default;
        void update(std::shared_ptr<AbstractAIController> aiController) override;
        bool getVisibility();
        bool getInRange();
};