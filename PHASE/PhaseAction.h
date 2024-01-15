#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"

class Joueur;
class Jeu;

class PhaseAction : public Phase {
public:
    static PhaseAction* getInstancePhaseAction();
    ~PhaseAction();

    PhaseAction(const PhaseAction&) = delete;
    PhaseAction& operator=(const PhaseAction&) = delete;

    virtual Phase* phaseSuivante() override;
    bool estAPhaseAction() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;


private:
    PhaseAction();
    static PhaseAction* instancePhaseAction;
};

#endif //DOMI_PHASEACTION_H
