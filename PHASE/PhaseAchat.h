#ifndef DOMI_PHASEACHAT_H
#define DOMI_PHASEACHAT_H

#include "Phase.h"

class PhaseAchat : public Phase {
public:
    virtual Phase* getPhaseSuivante() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;
private:
    PhaseAchat();
};

#endif //DOMI_PHASEACHAT_H
