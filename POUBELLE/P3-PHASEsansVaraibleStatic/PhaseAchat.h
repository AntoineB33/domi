#ifndef DOMI_PHASEACHAT_H
#define DOMI_PHASEACHAT_H

#include "Phase.h"
#include "PhaseAjustement.h"

class PhaseAchat : public Phase {
public:
    static PhaseAchat* getInstancePhaseAchat();
    ~PhaseAchat();

    PhaseAchat(const PhaseAchat&) = delete;
    PhaseAchat& operator=(const PhaseAchat&) = delete;

    virtual Phase* phaseSuivante() override;

private:
    PhaseAchat();
    static PhaseAchat instancePhaseAchat;
};

#endif // DOMI_PHASEACHAT_H