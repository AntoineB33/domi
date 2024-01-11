#include "Phase.h"

#include "Joueur.h"
#include "PhaseAction.h"

Phase* Phase::phaseCourante = PhaseAction::getInstancePhaseAction();

Phase::Phase(int nbINITachat, int nbINITaction, std::string  nomPhase): m_nbINITachat(nbINITachat), m_nbINITaction(nbINITaction), m_nomPhase(nomPhase){
}

Phase::~Phase() {
}

Phase* Phase::getPhaseCourante(){
    return Phase::phaseCourante;
}

void Phase::initJoueur(Joueur &j){
    j.initJoueur(m_nbINITachat,m_nbINITaction);
};

const std::string* Phase::getNomPhase() const {
    return &m_nomPhase;
}