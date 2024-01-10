#include "PhaseAction.h"


PhaseAction PhaseAction::instancePhaseAction = PhaseAction();
//Phase* Phase::phaseActuelle = PhaseAction::getInstancePhaseAction();

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
