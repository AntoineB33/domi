#include "Phase.h"

#include "Joueur.h"
#include "Jeu.h"
#include "PhaseAction.h"

#include <iostream>

Phase* Phase::phaseCourante = nullptr;

Phase::Phase(int nbINITachat, int nbINITaction, std::string  nomPhase): m_nbINITachat(nbINITachat), m_nbINITaction(nbINITaction), m_nomPhase(nomPhase){
}

Phase::~Phase() {
}

Phase* Phase::getFirstPhase(){
    Phase::phaseCourante = PhaseAction::getInstancePhaseAction();
    return Phase::phaseCourante;
}

void Phase::setPhaseCourante(Phase* p){
    phaseCourante = p;
}

Phase* Phase::getPhaseCourante(){
    return Phase::phaseCourante;
}

void Phase::jouerPhase(Jeu& jeu, Joueur& joueur){
    jeu.afficherCartesPlateau();
    joueur.afficherMain();
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

const std::string* Phase::getNomPhase() const {
    return &m_nomPhase;
}

bool Phase::estAPhaseAchat() {
    return false;
}

bool Phase::estAPhaseAction() {
    return false;
}

bool Phase::estAPhaseAjustement() {
    return false;
}