#include "PhaseAjustement.h"

PhaseAjustement PhaseAjustement::instancePhaseAjustement = PhaseAjustement();

PhaseAjustement* PhaseAjustement::getInstancePhaseAjustement() {
    return &instancePhaseAjustement;
}

PhaseAjustement::~PhaseAjustement() {

}

PhaseAjustement::PhaseAjustement() : Phase(0, 0) {

}

Phase* PhaseAjustement::phaseSuivante(){
    return PhaseAchat::getInstancePhaseAchat();
}
