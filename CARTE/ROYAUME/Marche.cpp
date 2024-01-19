#include "Marche.h"
#include "Jeu.h"

Marche* Marche::instanceMarche = new Marche("Marché",5,"+1 Carte +1 Action +1 Achat +1 Valeur");

Marche* Marche::makeMarche(){
    return Marche::instanceMarche;
}
Marche::~Marche(){
    delete Marche::instanceMarche;
}
Marche::Marche(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}

void Marche::faireAction(Joueur &joueur, Jeu &jeu) {
    joueur.piocher();
    ajoutAchat(joueur, 1);
    ajoutAction(joueur, 1);
    ajouterValeurSupp(joueur, 1);
    (void)jeu;

}

