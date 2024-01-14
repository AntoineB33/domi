#include "PhaseAction.h"
#include "PhaseAchat.h"

PhaseAction* PhaseAction::instancePhaseAction = new PhaseAction();
//Phase* Phase::phaseActuelle = PhaseAction::getInstancePhaseAction();

PhaseAction* PhaseAction::getInstancePhaseAction() {
    return instancePhaseAction;
}

PhaseAction::~PhaseAction() {
    delete PhaseAction::instancePhaseAction;
}

PhaseAction::PhaseAction() : Phase(0, 1) {

}

Phase* PhaseAction::phaseSuivante(){
    Phase::phaseCourante = PhaseAchat::getInstancePhaseAchat();
    return Phase::phaseCourante;
}
