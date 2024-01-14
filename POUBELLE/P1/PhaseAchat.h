#ifndef DOMI_PHASEACHAT_H
#define DOMI_PHASEACHAT_H

#include "Jeu.h"
#include "Phase.h"


class PhaseAchat : public Phase {
public:
    static PhaseAchat* getInstancePhaseAchat();
    ~PhaseAchat();

    PhaseAchat(const PhaseAchat&) = delete;
    PhaseAchat& operator=(const PhaseAchat&) = delete;

    virtual Phase* phaseSuivante() override;
    virtual void initialisationJoueur(Jeu jeu) override;

private:
    PhaseAchat();
    static PhaseAchat instancePhaseAchat;
};

#endif // DOMI_PHASEACHAT_H