#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"

class PhaseAction : public Phase {
public:
    virtual Phase* getPhaseSuivante() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;
private:
    PhaseAction();
};

#endif //DOMI_PHASEACTION_H
