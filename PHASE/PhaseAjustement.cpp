#include "PhaseAjustement.h"
#include "PhaseAction.h"

PhaseAjustement* PhaseAjustement::instancePhaseAjustement = new PhaseAjustement();

PhaseAjustement* PhaseAjustement::getInstancePhaseAjustement() {
    return instancePhaseAjustement;
}

PhaseAjustement::~PhaseAjustement() {
    delete PhaseAjustement::instancePhaseAjustement;
}

PhaseAjustement::PhaseAjustement() : Phase(0, 0, "PHASE AJUSTEMENT") {

}

Phase* PhaseAjustement::phaseSuivante(){
    Phase::phaseCourante = PhaseAction::getInstancePhaseAction();
    return Phase::phaseCourante;
}
