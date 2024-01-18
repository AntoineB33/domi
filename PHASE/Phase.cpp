#include "Phase.h"

#include "Joueur.h"
#include "Jeu.h"
#include "PhaseAction.h"

#include <iostream>

Phase* Phase::instance = nullptr;

Phase::Phase(std::string  nomPhase): m_nomPhase(nomPhase){
    instance = this;
}

Phase::~Phase() {
    delete instance;
}

const std::string* Phase::getNomPhase() const {
    return &m_nomPhase;
}

Phase* Phase::getInstance() {
    return instance;
}

Phase* Phase::getPhaseSuivante() {
    return instance;
}



void Phase::afficherPhase(Joueur& joueur){
    std::cout << "Phase " << *getNomPhase() << " du joueur " << joueur.getId() << "\n";
    std::cout << joueur.getNbAction() << " Action | " << joueur.getNbAction() << " Achats\n";
}

// void Phase::initJoueur(Joueur &j){
//     if(j.isInGodMode()) {
//         j.initJoueur(100,100);
//     } else {
//         j.initJoueur(m_nbINITachat,m_nbINITaction);
//     }
// };


