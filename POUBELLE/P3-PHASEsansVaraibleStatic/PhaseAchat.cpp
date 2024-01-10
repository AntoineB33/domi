#include "PhaseAchat.h"


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
