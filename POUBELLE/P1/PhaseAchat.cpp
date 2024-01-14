#include "PhaseAchat.h"
#include "PhaseAjustement.h"
#include "Jeu.h"

PhaseAchat PhaseAchat::instancePhaseAchat = PhaseAchat();

PhaseAchat* PhaseAchat::getInstancePhaseAchat() {
    return &instancePhaseAchat;
}

PhaseAchat::~PhaseAchat() {

}

PhaseAchat::PhaseAchat() : Phase(1, 0) {

}

Phase* PhaseAchat::phaseSuivante(){
    return PhaseAjustement::getInstancePhaseAjustement();
}

void PhaseAchat::initialisationJoueur(Jeu jeu){
    jeu.initialiseNbAchatNbAction(1, 0);
}