#include "PhaseAchat.h"
#include "PhaseAjustement.h"
#include "jeu.h"
#include <iostream>

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

bool PhaseAchat::estAPhaseAchat() {
    return true;
}

void PhaseAchat::jouerPhase(Jeu& jeu, Joueur& joueur){
    Phase::afficherPhase();
    std::cout << "Vous pouvez acheter des cartes.\n";
    (void)jeu;
    (void)joueur;
}