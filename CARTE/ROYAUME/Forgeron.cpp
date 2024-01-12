#include "Forgeron.h"
#include "Jeu.h"

Forgeron* Forgeron::instanceForgeron = new Forgeron("Forgeron",4,"+3 Cartes");

Forgeron* Forgeron::makeForgeron(){
    return Forgeron::instanceForgeron;
}
Forgeron::~Forgeron(){
    delete Forgeron::instanceForgeron;
}
Forgeron::Forgeron(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Forgeron::faireAction(Joueur &joueur, Jeu &jeu) {
    piocherCarteDeck(joueur, 3);
    (void)jeu;
}