#ifndef DOMI_PHASEAJ_H
#define DOMI_PHASEJ_H

#include "Phase.h"

class PhaseAjustement : public Phase {
public:
    PhaseAjustement(const std::string& name);
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;

    
    Phase& getPhaseSuivante() override;
    const std::string& getNomPhase() const override;
    
    static PhaseAjustement& getInstance();
    bool dernierePhase() const override;
private:
    const std::string m_nomPhase;
    static PhaseAjustement instance;
};

#endif //DOMI_PHASEACTION_H
