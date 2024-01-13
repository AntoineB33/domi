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


    {
        int nbJoueur = 0;
        while(nbJoueur < 2 || nbJoueur > 4) {
            std::cout<<"Combien de joueur (2 - 4)?\n";
            std::cin>>nbJoueur;
        }
        Jeu j = Jeu(nbJoueur);
        j.lancementJeu();

    }

    std::cout<<"\n\n\n\n====== FIN ======\n\n\n\n";
    return 0;
}
