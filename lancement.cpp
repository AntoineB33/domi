#include <iostream>
#include "Carte.h"
#include "Or.h"
#include "Tresor.h"
#include "Cuivre.h"
#include "Domaine.h"
#include "Joueur.h"
#include "Jeu.h"
#include "Marche.h"

#include <map>

int main() {
    Marche* m = Marche::makeMarche();
    std::cout<<*m<<"\n";
    Carte* c =Marche::makeMarche();
    std::cout<<*c<<"\n";


    {
        int nbJoueur;
        std::cout<<"Combien de joueur ?\n";
        std::cin>>nbJoueur;
        Jeu j = Jeu();
        j.lancementJeu();

    }

    std::cout<<"\n\n\n\n====== FIN ======\n\n\n\n";
    return 0;
}
