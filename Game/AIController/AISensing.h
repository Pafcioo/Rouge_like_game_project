#pragma once

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
        bool isEntityVisible;
    public:
        VisionSensing(float range);
        ~VisionSensing() = default;
        void update(std::shared_ptr<AbstractAIController> aiController) override;
        bool getVisibility();
};