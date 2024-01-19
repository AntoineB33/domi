#include "PhaseAjustement.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

// PhaseAction PhaseAction::instance;

// PhaseAction::PhaseAction() : Phase("PHASE ACTION") {}

PhaseAjustement::PhaseAjustement(const std::string& name) : m_nomPhase(name) {}
PhaseAjustement PhaseAjustement::instance("PHASE ACTION");


Phase& PhaseAjustement::getPhaseSuivante() {
    return PhaseAchat::getInstance();
}


PhaseAjustement& PhaseAjustement::getInstance() {
    return instance;
}
bool PhaseAjustement::dernierePhase() const {
    return true;
}

const std::string& PhaseAjustement::getNomPhase() const {
    return m_nomPhase;
}


/// IHM

void PhaseAjustement::jouerPhase(Jeu& jeu, Joueur& joueur) {
    joueur.mettreMainDansDefausse();
    std::cout << "Vous avez  valeur disponible.\n";
    if(joueur.isInGodMode()) {
        joueur.piocher(1000);
    } else {
        joueur.piocher(5);
    }
    (void)jeu;
}