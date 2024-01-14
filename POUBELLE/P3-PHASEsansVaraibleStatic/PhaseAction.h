#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"
#include "PhaseAchat.h"

class PhaseAction : public Phase {
public:
    static PhaseAction* getInstancePhaseAction();
    ~PhaseAction();

    PhaseAction(const PhaseAction&) = delete;
    PhaseAction& operator=(const PhaseAction&) = delete;

    virtual Phase* phaseSuivante() override;


private:
    PhaseAction();
    static PhaseAction instancePhaseAction;
};

#endif //DOMI_PHASEACTION_H
