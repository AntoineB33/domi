#include "Chapelle.h"
#include "Jeu.h"

Chapelle* Chapelle::instanceChapelle = new Chapelle("Chapelle",2,"Ecartez jusqu'à 4 cartes de votre main.");

Chapelle* Chapelle::makeChapelle(){
    return Chapelle::instanceChapelle;
}
Chapelle::~Chapelle(){
    delete Chapelle::instanceChapelle;
}
Chapelle::Chapelle(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}


void Chapelle::faireAction(Joueur &joueur, Jeu &jeu) {
    (void)joueur;
    (void)jeu;
    // joueur.ecarter(jeu, 4);
}