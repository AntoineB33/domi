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
        Jeu j = Jeu();
        for(int i = 0; i < j.getNbJoueur(); i++){
            std::cout<<*j.getJoueur(i)<<std::endl;

            //std::cout<<"nb valeur disponible : "<<j.getJoueur(i) -> nbValeurDisponible()<<"\n";
            j.getJoueur(i) -> piocherCarteDeck(12);
            std::cout<<*j.getJoueur(i)<<std::endl;
            std::cout<<"==== mettre carte en court d'utilisation ===="<<std::endl;
            std::map<Carte*,int> m;
            for(auto entry : j.getJoueur(i) -> getMain()){
                Carte::ajoutSuppCarte(m,entry.first,entry.second);
            }
            for(auto entry : m){
                j.getJoueur(i) -> mettreEncoursDutilisationCartes(entry.first, entry.second);
            }
            j.getJoueur(i) -> prendreCartePlateau(Marche::makeMarche(),j);
            std::cout<<*j.getJoueur(i)<<std::endl;
            j.getJoueur(i) -> defausserCarte();
            j.getJoueur(i) -> mettreDefausseDansDeck();
            std::cout<<*j.getJoueur(i)<<std::endl;
        }

        //j.getJoueur(0) -> nbValeurDisponible();

        //j.afficherCartesPlateau();


    }


    std::cout<<"\n\n\n\n====== FIN ======\n\n\n\n";
    return 0;
}
