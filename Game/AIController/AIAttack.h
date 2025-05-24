#pragma once

class AbstractAIController;

class AbstractAIAttack
{
    protected:
        int attackMulti;
    public:
        virtual ~AbstractAIAttack() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class AIAttack : public AbstractAIAttack
{
    public:
        AIAttack(int attack);
        ~AIAttack() = default;
        void update(std::shared_ptr<AbstractAIController> aiController);
};