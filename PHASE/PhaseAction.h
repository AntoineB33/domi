#ifndef DOMI_PHASEACTION_H
#define DOMI_PHASEACTION_H

#include "Phase.h"

class PhaseAction : public Phase {
public:
    PhaseAction(const std::string& name);
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;

    
    Phase& getPhaseSuivante() override;
    const std::string& getNomPhase() const override;
    
    static PhaseAction& getInstance();
private:
    const std::string m_nomPhase;
    static PhaseAction instance;
};

#endif //DOMI_PHASEACTION_H
