#include "Mine.h"
#include "Jeu.h"

Mine* Mine::instanceMine = new Mine("Mine",3,"Ecartez une carte Trésor de votre main.\nGagnez une carte Trésor coûtant jusqu'à 3 Pièces de plus ; ajoutez cette carte à votre main.");

Mine* Mine::makeMine(){
    return Mine::instanceMine;
}
Mine::~Mine(){
    delete Mine::instanceMine;
}
Mine::Mine(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Mine::faireAction(Joueur &joueur, Jeu &jeu) {
    augmenterTresor(jeu, joueur, 3);
    (void)jeu;
}