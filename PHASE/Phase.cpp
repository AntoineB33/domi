#include "Phase.h"

#include "Joueur.h"
#include "PhaseAction.h"

#include <iostream>

Phase* Phase::phaseCourante = nullptr;

Phase::Phase(int nbINITachat, int nbINITaction, std::string  nomPhase): m_nbINITachat(nbINITachat), m_nbINITaction(nbINITaction), m_nomPhase(nomPhase){
}

Phase::~Phase() {
}

void Phase::setPhaseCourante(Phase* p){
    phaseCourante = p;
}

Phase* Phase::getPhaseCourante(){
    return Phase::phaseCourante;
}

void Phase::initJoueur(Joueur &j){
    if(j.isInGodMode()) {
        j.initJoueur(100,100);
    } else {
        j.initJoueur(m_nbINITachat,m_nbINITaction);
    }
};

const std::string* Phase::getNomPhase() const {
    return &m_nomPhase;
}