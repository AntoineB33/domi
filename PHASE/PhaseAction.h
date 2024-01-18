#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"

class PhaseAction : public Phase {
public:
    PhaseAction(const std::string& name);
    // virtual Phase* getPhaseSuivante() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;
    // static PhaseAction instance;

    
    Phase& getPhaseSuivante() override;
    const std::string& getNomPhase() const override;
    
    static PhaseAction& getInstance();
private:
    const std::string m_nomPhase;
    static PhaseAction instance;
    // PhaseAction();
};

#endif //DOMI_PHASEACTION_H
