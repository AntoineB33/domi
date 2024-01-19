#include "Atelier.h"
#include "Jeu.h"
#include "Joueur.h"

Atelier* Atelier::instanceAtelier = new Atelier("Atelier",3,"Recevez une carte coutant jusqu'à 4");

Atelier* Atelier::makeAtelier(){
    return Atelier::instanceAtelier;
}
Atelier::~Atelier(){
    delete Atelier::instanceAtelier;
}
Atelier::Atelier(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Atelier::faireAction(Joueur &joueur, Jeu &jeu) {
    joueur.commandeRecevoirCartePlateau(4);
    (void)jeu;
}