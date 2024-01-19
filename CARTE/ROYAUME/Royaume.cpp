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


void Royaume::jouerAction(Joueur &joueur, Jeu &jeu) {
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




