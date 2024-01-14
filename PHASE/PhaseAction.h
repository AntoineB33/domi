#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"

class PhaseAction : public Phase {
public:
    static PhaseAction* getInstancePhaseAction();
    ~PhaseAction();

    PhaseAction(const PhaseAction&) = delete;
    PhaseAction& operator=(const PhaseAction&) = delete;

    virtual Phase* phaseSuivante() override;
    bool estAPhaseAction() override;


private:
    PhaseAction();
    static PhaseAction* instancePhaseAction;
};

#endif //DOMI_PHASEACTION_H
