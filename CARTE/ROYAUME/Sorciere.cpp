#include "Sorciere.h"
#include "Jeu.h"

Sorciere* Sorciere::instanceSorciere = new Sorciere("Sorciere",5,"+2 Cartes\nTous vos adversaires reçoivent une carte Malédiction.");

Sorciere* Sorciere::makeSorciere(){
    return Sorciere::instanceSorciere;
}
Sorciere::~Sorciere(){
    delete Sorciere::instanceSorciere;
}
Sorciere::Sorciere(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Sorciere::faireAction(Joueur &joueur, Jeu &jeu) {
    jeu.nop();
    (void)joueur;
}