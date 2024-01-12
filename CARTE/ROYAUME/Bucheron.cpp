#include "Bucheron.h"
#include "Jeu.h"

#include <iostream>

Bucheron* Bucheron::instanceBucheron = new Bucheron("Bucheron",3,"+1 Achat +2 Valeur");

Bucheron* Bucheron::makeBucheron(){
    return Bucheron::instanceBucheron;
}
Bucheron::~Bucheron(){
    delete Bucheron::instanceBucheron;
}
Bucheron::Bucheron(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Bucheron::faireAction(Joueur &joueur, Jeu &jeu) {
    ajoutAchat(joueur, 1);
    ajouterValeurSupp(joueur, 2);
    (void)jeu;
}