#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

#include "Jeu.h"

class Phase {
public:
    Phase(int nbMAxachat, int nbMAXaction);
    virtual ~Phase();
    virtual Phase* phaseSuivante() = 0;
    virtual void initialisationJoueur(Jeu jeu) = 0;


private:
    const int m_nbMAXachat;
    const int m_nbMAXaction;

};


#endif //DOMI_PHASE_H
