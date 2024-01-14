#include "PhaseAction.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include <iostream>

PhaseAction* PhaseAction::instancePhaseAction = new PhaseAction();
//Phase* Phase::phaseActuelle = PhaseAction::getInstancePhaseAction();

PhaseAction* PhaseAction::getInstancePhaseAction() {
    return instancePhaseAction;
}

PhaseAction::~PhaseAction() {
    delete PhaseAction::instancePhaseAction;
}

PhaseAction::PhaseAction() : Phase(0, 1, "PHASE ACTION") {
    Phase::setPhaseCourante(this);
}

Phase* PhaseAction::phaseSuivante(){
    Phase::phaseCourante = PhaseAchat::getInstancePhaseAchat();
    return Phase::phaseCourante;
}

bool PhaseAction::estAPhaseAction() {
    return true;
}
