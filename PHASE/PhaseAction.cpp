#include "PhaseAjustement.h"
#include "PhaseAchat.h"
#include "PhaseAction.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

// PhaseAction PhaseAction::instance;

// PhaseAction::PhaseAction() : Phase("PHASE ACTION") {}

PhaseAction::PhaseAction(const std::string& name) : m_nomPhase(name) {}
PhaseAction PhaseAction::instance("PHASE ACTION");

Phase& PhaseAction::getPhaseSuivante() {
    return PhaseAchat::getInstance();
}

const std::string& PhaseAction::getNomPhase() const {
    return m_nomPhase;
}

// Phase* PhaseAction::getPhaseSuivante() {
//     return PhaseAchat::getInstance();
// }

bool estTypeAction(Carte* carte) {
    return carte->getTypeCarte() == TypeRoyaume;
}

PhaseAction& PhaseAction::getInstance() {
    return instance;
}


/// IHM


void PhaseAction::jouerPhase(Jeu& jeu, Joueur& joueur) {
    if(!joueur.typeDansMain(TypeRoyaume)) {
        return;
    }
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
    
    std::string commande;
    while(joueur.getNbAction()>0) {
        jeu.afficherReserve();
        joueur.afficherUtilise();
        afficherPhase(joueur);
        joueur.afficherMain(true, [](Carte* carte) -> bool {
            return carte->getTypeCarte() == TypeRoyaume;
        });
        int idCarte = 0;
        Carte* carte = joueur.demandeChercherCarte(joueur.getMain(), commande, idCarte);
        if(carte == nullptr){
            break;
        }
        if(carte->getTypeCarte() != TypeRoyaume) {
            std::cout << DIM_TEXT << RED << "Ce n'est pas une carte Royaume.\n" << RESET;
            continue;
        }
        carte->jouerAction(joueur, jeu);
        joueur.mainVersDeck(carte);
        joueur.addNbActionPhase(-1);
    }
}