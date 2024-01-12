#include "Village.h"
#include "Jeu.h"

Village* Village::instanceVillage = new Village("Marché", 3," +1 Carte  +2 Actions");

Village* Village::makeVillage(){
    return Village::instanceVillage;
}
Village::~Village(){
    delete Village::instanceVillage;
}
Village::Village(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}

void Village::faireAction(Joueur &joueur, Jeu &jeu) {
    piocherCarteDeck(joueur);
    ajoutAction(joueur, 2);
    (void)jeu;
}