#include "Royaume.h"
#include <iostream>

Royaume::Royaume(std::string nom, int cout, std::string description)
        : Carte(nom,TypeRoyaume,cout), m_description(description) {}

Royaume::~Royaume() {}

std::string Royaume::getDescription() const {
    return m_description;
}

std::ostream& operator<<(std::ostream& os, const Royaume& royaume){
    os<< reinterpret_cast<const Carte&>(royaume);
    return os;
}


void Royaume::jouerAction(Joueur &joueur, Jeu &jeu) {
    faireAction(joueur, jeu);
}
void Royaume::ajoutAction(Joueur & joueur, int nb){
    joueur.addNbActionPhase(nb);
}
void Royaume::ajoutAchat(Joueur & joueur, int nb) {
    joueur.addNbActionPhase(nb);
}
void Royaume::supprimerCarte(Joueur & joueur, Carte* c, int quantite){
    joueur.supprimerCarteMain(c,quantite);
}
void Royaume::piocherCarteDeck(Joueur &joueur, int quantite) {
    joueur.piocherCarteDeck(quantite);
}
void Royaume::ajouterValeurSupp(Joueur &joueur, int nbValeurSupp) {
    joueur.ajouterRetirerValeurSupp(nbValeurSupp);
}
void Royaume::recevoirCarte(Joueur &joueur, Jeu &jeu, int coutMax) {
    (void)jeu;
    (void)joueur;
    (void)coutMax;
    // joueur.recevoirCarte(jeu,coutMax);
}
void Royaume::ecarter(Joueur &joueur, Jeu &jeu, int quantite) {
    (void)jeu;
    (void)joueur;
    (void)quantite;
    // joueur.ecarter(jeu,quantite);
}



