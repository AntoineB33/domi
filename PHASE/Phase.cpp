#include "Phase.h"

#include "Joueur.h"
#include "Jeu.h"
#include "PhaseAction.h"
#include "CouleurTerminal.h"

#include <iostream>



const std::string& Phase::getNomPhase() const {
    return m_nomPhase;
}

bool Phase::dernierePhase() const {
    return false;
}

void Phase::afficherPhase(Joueur& joueur){
    std::cout << BOLD_ON << GREEN << getNomPhase() << " du joueur " << joueur.getId() << "\n";
    std::cout << joueur.getNbAction() << " Action | " << joueur.getNbAchat() << " Achats\n" << RESET;
}



