#ifndef DOMI_PHASEAJUSTEMENT_H
#define DOMI_PHASEAJUSTEMENT_H

#include "Phase.h"
#include "PhaseAchat.h"

class PhaseAjustement : public Phase {
public:
    static PhaseAjustement* getInstancePhaseAjustement();
    ~PhaseAjustement();

    PhaseAjustement(const PhaseAjustement&) = delete;
    PhaseAjustement& operator=(const PhaseAjustement&) = delete;

    virtual Phase* phaseSuivante() override;

private:
    PhaseAjustement();
    static PhaseAjustement instancePhaseAjustement;
};

#endif // DOMI_PHASEAJUSTEMENT_H
