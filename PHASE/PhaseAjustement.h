#ifndef DOMI_PHASEAJUSTEMENT_H
#define DOMI_PHASEAJUSTEMENT_H

#include "Phase.h"

class PhaseAjustement : public Phase {
public:
    virtual Phase* getPhaseSuivante() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;
private:
    PhaseAjustement();
};

#endif //DOMI_PHASEAJUSTEMENT_H
