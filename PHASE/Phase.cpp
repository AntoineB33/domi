#include "Phase.h"

#include "Jeu.h"
#include "PhaseAction.h"

Phase* Phase::phaseCourante = PhaseAction::getInstancePhaseAction();

Phase::Phase(int nbINITachat, int nbINITaction): m_nbINITachat(nbINITachat), m_nbINITaction(nbINITaction){
}

Phase::~Phase() {
}

Phase* Phase::getPhaseCourante(){
    return Phase::phaseCourante;
}

void Phase::initJeu(Jeu &jeu){
    jeu.initJoueurs(m_nbINITachat,m_nbINITaction);
};