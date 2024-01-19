#include "PhaseAjustement.h"
#include "PhaseAchat.h"
#include "PhaseAction.h"
#include "Phase.h"
#include "Joueur.h"
#include "Jeu.h"
#include "CouleurTerminal.h"
#include <iostream>

// PhaseAchat PhaseAchat::instance;

// PhaseAchat::PhaseAchat() : Phase("PHASE ACHAT") {
// }
PhaseAchat::PhaseAchat(const std::string& name) : m_nomPhase(name) {
}

PhaseAchat PhaseAchat::instance("PHASE ACHAT");

Phase& PhaseAchat::getPhaseSuivante() {
    return PhaseAjustement::getInstance();
}

const std::string& PhaseAchat::getNomPhase() const {
    return m_nomPhase;
}

// Phase* PhaseAchat::getPhaseSuivante() {
//     return PhaseAjustement::getInstance();
// }

bool estTypeTresor(Carte* carte) {
    return carte->getTypeCarte() == TypeTresor;
}

// static PhaseAchat& getInstance() {
//     return instance;
// }
PhaseAchat& PhaseAchat::getInstance() {
    return instance;
}



/// IHM


void PhaseAchat::jouerPhase(Jeu& jeu, Joueur& joueur) {
    std::string commande;
    while(joueur.getNbAchat()>0) {
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
        joueur.afficherMain(true, [](Carte* carte) -> bool {
            return carte->getTypeCarte() == TypeTresor;
        }, lastId);
        int idCarte = 0;
        std::vector<std::pair<Carte *, int>>& reserve = jeu.getReserve();
        const std::vector<std::pair<Carte *, int>>& m_main = joueur.getMain();
        std::vector<std::pair<Carte *, int>> concatenatedVector;
        concatenatedVector.insert(concatenatedVector.end(), reserve.begin(), reserve.end());
        concatenatedVector.insert(concatenatedVector.end(), m_main.begin(), m_main.end());
        Carte* carte = joueur.demandeChercherCarte(concatenatedVector, commande, idCarte);
        if(carte == nullptr){
            break;
        }
        if(idCarte<lastId) {
            if(carte->getCout() > disponible) {
                std::cout << DIM_TEXT << RED << "Vous n'avez pas assez de valeur pour acheter cette carte.\n" << RESET;
                continue;
            }
            joueur.reserveVersDeck(jeu, carte);
            joueur.addNbAchatPhase(-1);
        } else {
            if(carte->getTypeCarte() != TypeTresor) {
                std::cout << DIM_TEXT << RED << "Ce n'est pas une carte trésor.\n" << RESET;
                continue;
            }
            joueur.mainVersUtilise(carte);
        }
    }
    joueur.mettreUtiliseDansDefausse();
}