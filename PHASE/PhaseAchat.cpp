#include "PhaseAjustement.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

PhaseAchat::PhaseAchat() : Phase("PHASE ACHAT") {
}

Phase* PhaseAchat::getPhaseSuivante() {
    return PhaseAjustement::getInstance();
}


/// IHM


void PhaseAchat::jouerPhase(Jeu& jeu, Joueur& joueur) {
    if(!joueur.typeDansMain(TypeTresor)) {
        return;
    }
    afficherPhase(jeu, joueur);
    std::cout << "Vous pouvez jouer des cartes.\n";
    const std::vector<std::pair<Carte*, int>>& main = joueur.getMain();
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