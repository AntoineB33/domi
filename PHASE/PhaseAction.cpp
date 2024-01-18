#include "PhaseAction.h"
#include "PhaseAchat.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

PhaseAction::PhaseAction() : Phase("PHASE ACTION") {
}

Phase* PhaseAction::getPhaseSuivante() {
    return PhaseAchat::getInstance();
}

bool estTypeAction(Carte* carte) {
    return carte->getTypeCarte() == TypeRoyaume;
}


/// IHM


void PhaseAction::jouerPhase(Jeu& jeu, Joueur& joueur) {
    if(!joueur.typeDansMain(TypeRoyaume)) {
        return;
    }
    jeu.afficherReserve();
    // joueur.afficherMain();
    // joueur.afficherUtilise();
    // afficherPhase(joueur);
    // std::cout << "Vous pouvez jouer des cartes.\n";
    // const std::vector<std::pair<Carte*, int>>& main = joueur.getMain();
    // int nbAction = joueur.getNbAction();
    // std::string commande;
    // for(int i = 0; i<nbAction; i++) {
    //     Carte::afficher(main, estTypeAction);
    //     Carte* carte = joueur.demandeChercherCarte(main, commande);
    //     if(carte == nullptr){
    //         break;
    //     }
    //     carte->jouerAction(joueur, jeu);
    //     joueur.mainVersUtilise(carte);
    // }
}