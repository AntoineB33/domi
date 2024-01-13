#include "Phase.h"

#include "Joueur.h"
#include "PhaseAction.h"

#include <iostream>

Phase* Phase::phaseCourante = PhaseAction::getInstancePhaseAction();

Phase::Phase(int nbINITachat, int nbINITaction, std::string  nomPhase): m_nbINITachat(nbINITachat), m_nbINITaction(nbINITaction), m_nomPhase(nomPhase){
}

Phase::~Phase() {
}

Phase* Phase::getPhaseCourante(){
    return Phase::phaseCourante;
}

void Phase::initJoueur(Joueur &j){
    std::cout << "Phase::initJoueur" << std::endl;
    std::cout << "m_nbINITachat: " << m_nbINITachat << std::endl;
    std::cout << "m_nbINITaction: " << m_nbINITaction << std::endl;
    j.initJoueur(m_nbINITachat,m_nbINITaction);
};

const std::string* Phase::getNomPhase() const {
    return &m_nomPhase;
}