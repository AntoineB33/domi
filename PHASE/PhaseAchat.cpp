#include "PhaseAchat.h"
#include "PhaseAjustement.h"

PhaseAchat* PhaseAchat::instancePhaseAchat = new PhaseAchat();

PhaseAchat* PhaseAchat::getInstancePhaseAchat() {
    return instancePhaseAchat;
}

PhaseAchat::~PhaseAchat() {
    delete PhaseAchat::instancePhaseAchat;
}

PhaseAchat::PhaseAchat() : Phase(1, 0, "PHASE ACHAT") {
}

Phase* PhaseAchat::phaseSuivante(){
    Phase::phaseCourante = PhaseAjustement::getInstancePhaseAjustement();
    return Phase::phaseCourante;
}
