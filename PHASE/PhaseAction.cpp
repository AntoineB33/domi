#include "PhaseAction.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

PhaseAction* PhaseAction::instancePhaseAction = new PhaseAction();
//Phase* Phase::phaseActuelle = PhaseAction::getInstancePhaseAction();

PhaseAction* PhaseAction::getInstancePhaseAction() {
    return instancePhaseAction;
}

PhaseAction::~PhaseAction() {
    delete PhaseAction::instancePhaseAction;
}

PhaseAction::PhaseAction() : Phase(0, 1, "PHASE ACTION") {
    Phase::setPhaseCourante(this);
}

Phase* PhaseAction::phaseSuivante(){
    Phase::phaseCourante = PhaseAchat::getInstancePhaseAchat();
    return Phase::phaseCourante;
}

bool PhaseAction::estAPhaseAction() {
    return true;
}


/// IHM


void PhaseAction::jouerPhase(Jeu& jeu, Joueur& joueur){
    if(!joueur.typeDansMain(TypeTresor)) {
        return;
    }
    Phase::jouerPhase(jeu, joueur);
    std::cout << "Vous pouvez jouer des cartes.\n";
    const std::map<Carte*, int>& main = joueur.getMain();
    for(std::pair<Carte*, int> carte : main){
        if(carte.first->getTypeCarte() == TypeTresor){
            std::cout << "-> ";
        } else {
            std::cout << "   ";
        }
        std::cout << carte.second << " " << carte.first->getNom() << " ";
        std::cout <<DIM_TEXT<<GRAY<< carte.first->getDesc() << "\n" << RESET;
    }
    std::string commande;
    int nbAction = joueur.getNbAction();
    for(int i = 0; i<nbAction; i++) {
        Carte* carte = joueur.demandeChercherCarte(main, commande);
        if(carte == nullptr){
            break;
        }
        carte->jouerAction(joueur, jeu);
    }
}