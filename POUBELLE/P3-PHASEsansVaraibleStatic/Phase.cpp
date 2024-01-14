#include "Phase.h"
#include "Jeu.h"

Phase::Phase(int nbMAXachat, int nbMAXaction): m_nbMAXachat(nbMAXachat), m_nbMAXaction(nbMAXaction){
}

Phase::~Phase() {
}

void Phase::initialiseNbAchatNbAction(Jeu &jeu){
    jeu.initialiseNbAchatNbAction(m_nbMAXachat, m_nbMAXaction);
}
