#include "Royaume.h"

#include "CouleurTerminal.h"
#include <functional>
#include <iostream>

Royaume::Royaume(std::string nom, int cout, std::string description)
        : Carte(nom,TypeRoyaume,cout) {
    m_description = " (Cout: " + std::to_string(cout) + ", Desc: " + description +")";
}

Royaume::~Royaume() {}


std::string& Royaume::getDesc() {
    return m_description;
}

std::string Royaume::getDescription() const {
    return m_description;
}

std::ostream& operator<<(std::ostream& os, const Royaume& royaume){
    os<< reinterpret_cast<const Carte&>(royaume);
    os<< "\tDESCRIPTION : "<<royaume.getDescription();
    return os;
}


void Royaume::jouerAction(Joueur &joueur, Jeu &jeu) {
    std::cout<<DIM_TEXT<<BOLD_ON"DESCRIPTION : "<<RESET;
    std::cout<<DIM_TEXT<<getDescription()<<"\n"<<RESET;
    faireAction(joueur, jeu);
}

void Royaume::ajoutAction(Joueur & joueur, int nb){
    joueur.addNbActionPhase(nb);
}

void Royaume::ajoutAchat(Joueur & joueur, int nb) {
    joueur.addNbAchatPhase(nb);
}

void Royaume::ajouterValeurSupp(Joueur &joueur, int nbValeurSupp) {
    joueur.ajouterRetirerValeurSupp(nbValeurSupp);
}



//////////////////////////////IHM
void Royaume::commandeRecevoirCartePlateau(Joueur& joueur, Jeu& jeu, int coutMax) {
    std::string commande;
    
    jeu.afficherReserve(true, [coutMax](Carte* carte) -> bool {
        return carte->getCout() <= coutMax;
    });
    joueur.afficherUtilise();
    std::cout << "Choisissez une carte coutant jusqu'à " << coutMax << "\n";
    joueur.afficherMain();
    int idCarte = 0;
    Carte* carte = joueur.demandeChercherCarte(jeu.getReserve(), commande, idCarte);
    if(carte == nullptr){
        return;
    }
    if(carte->getCout() > coutMax) {
        std::cout << "Vous n'avez pas assez de valeur pour acheter cette carte.\n";
    }
    joueur.mainVersUtilise(carte);
}



