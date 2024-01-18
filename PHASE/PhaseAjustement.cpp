#include "PhaseAjustement.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

PhaseAjustement::PhaseAjustement() : Phase("PHASE ACHAT") {
}

Phase* PhaseAjustement::getPhaseSuivante() {
    return nullptr;
}


/// IHM


void PhaseAjustement::jouerPhase(Jeu& jeu, Joueur& joueur) {
    joueur.mettreMainDansDefausse();
    joueur.piocher(5);
    (void)jeu;
}