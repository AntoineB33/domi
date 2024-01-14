#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

#include <string>

class Joueur;

class Phase {
public:
    Phase(int nbINITachat, int nbINITaction, std::string nomPhase);
    virtual ~Phase();
    virtual Phase* phaseSuivante() = 0;

    static Phase* getPhaseCourante();
    void initJoueur(Joueur &joueur);
    const std::string* getNomPhase() const;
    static void setPhaseCourante(Phase* phaseCourante);
    virtual bool estAPhaseAchat();
    virtual bool estAPhaseAction();
    virtual bool estAPhaseAjustement();

protected:
    static Phase* phaseCourante;


private:
    const int m_nbINITachat;
    const int m_nbINITaction;
    const std::string m_nomPhase;
};


#endif //DOMI_PHASE_H
