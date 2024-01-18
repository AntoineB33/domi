#ifndef DOMI_PHASEACHAT_H
#define DOMI_PHASEACHAT_H

#include "Phase.h"

class PhaseAchat : public Phase {
public:
    PhaseAchat(const std::string& name);
    // virtual Phase* getPhaseSuivante() override;
    void jouerPhase(Jeu& jeu, Joueur& joueur) override;
    // static Phase* getInstance() override;

    
    Phase& getPhaseSuivante() override;
    const std::string& getNomPhase() const override;
    
    static PhaseAchat& getInstance();
private:
    const std::string m_nomPhase;
    static PhaseAchat instance;
    // PhaseAchat();
};

#endif //DOMI_PHASEACHAT_H
