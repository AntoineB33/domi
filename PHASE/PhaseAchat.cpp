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

bool estTypeTresor(Carte* carte) {
    return carte->getTypeCarte() == TypeTresor;
}


/// IHM


void PhaseAchat::jouerPhase(Jeu& jeu, Joueur& joueur) {
    const std::vector<std::pair<Carte*, int>>& main = joueur.getMain();
    int nbAction = joueur.getNbAction();
    std::string commande;
    for(int i = 0; i<nbAction; i++) {
        int disponible = joueur.nbValeurDisponible();
        if(!jeu.hasCarteAchetable(disponible)) {
            std::cout << "Il n'y a plus de carte achetable.\n";
            return;
        }
        int lastId = jeu.afficherReserve(true, [disponible](Carte* carte) -> bool {
            return carte->getCout() <= disponible;
        });
        joueur.afficherUtilise();
        afficherPhase(joueur);
        joueur.afficherMain([](Carte* carte) -> bool {
            return carte->getTypeCarte() == TypeTresor;
        }, lastId);
        int idCarte = 0;
        Carte* carte = joueur.demandeChercherCarte(main, commande, idCarte);
        if(carte == nullptr){
            break;
        }
        if(idCarte<lastId) {
            joueur.mainVersUtilise(carte);
        } else {
            joueur.acheterCarte(jeu, carte);
        }
        joueur.addNbAchatPhase(-1);
    }
}