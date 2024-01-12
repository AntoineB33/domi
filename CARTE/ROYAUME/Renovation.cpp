#include "Renovation.h"
#include "Jeu.h"

Renovation* Renovation::instanceRenovation = new Renovation("Renovation",4,"Ecartez une carte Action de votre main.\nRecevez une carte coûtant jusqu'à 2 de plus que la carte écartée.");

Renovation* Renovation::makeRenovation(){
    return Renovation::instanceRenovation;
}
Renovation::~Renovation(){
    delete Renovation::instanceRenovation;
}
Renovation::Renovation(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Renovation::faireAction(Joueur &joueur, Jeu &jeu) {
    int cout = joueur.commandeEcarter(jeu, 1);
    commandeRecevoirCartePlateau(joueur, jeu, cout+2);
}