#include "Sorciere.h"
#include "Malediction.h"
#include "Jeu.h"

Sorciere* Sorciere::instanceSorciere = new Sorciere("Sorciere",5,"+2 Cartes. Tous vos adversaires reçoivent une carte Malédiction.");

Sorciere* Sorciere::makeSorciere() {
    return Sorciere::instanceSorciere;
}
Sorciere::~Sorciere() {
    delete Sorciere::instanceSorciere;
}
Sorciere::Sorciere(std::string nom, int cout,std::string description) : Royaume(nom,cout,description) {}


void Sorciere::faireAction(Joueur &joueur, Jeu &jeu) {
    joueur.piocher(2);
    jeu.ajoutCartesDefausses(Malediction::makeMalediction(), joueur.getId(), 2);
}