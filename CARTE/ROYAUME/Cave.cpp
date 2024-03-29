#include "Cave.h"
#include "Jeu.h"

Cave* Cave::instanceCave = new Cave("Cave",3,"+1 Achat  Défaussez autant de cartes que vous voulez. +1 Carte par carte défaussée.");

Cave* Cave::makeCave(){
    return Cave::instanceCave;
}
Cave::~Cave(){
    delete Cave::instanceCave;
}
Cave::Cave(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Cave::faireAction(Joueur &joueur, Jeu &jeu) {
    jeu.nop();
    ajoutAchat(joueur, 1);
    defausserInfin(joueur, jeu);
}