#include "PhaseAction.h"

PhaseAction PhaseAction::instancePhaseAction = PhaseAction();

PhaseAction* PhaseAction::getInstancePhaseAction() {
    return &instancePhaseAction;
}

PhaseAction::~PhaseAction() {

}

PhaseAction::PhaseAction() : Phase(0, 1) {

}

Phase* PhaseAction::phaseSuivante(){
    return PhaseAchat::getInstancePhaseAchat();
}

void PhaseAction::initialisationJoueur(Jeu jeu){
    jeu.initialiseNbAchatNbAction(0, 1);
}