#ifndef DOMI_JEU_H
#define DOMI_JEU_H

#include <vector>
#include "Joueur.h"

#include "Phase.h"
#include "Carte.h"

class Jeu {
public:
    Jeu(int nbJoueur = 2);
    virtual ~Jeu();

    void nop();

    int getNbJoueur();
    Joueur* getJoueur(int i) ;

    void initJoueurs(int nbAchatNEW, int nbActionNEW);
    void afficherCartesPlateau();

    bool carteDisponible(Carte* carte);//si elle peut etre encore achetée
    bool retirerCarteDisponible(Carte* carte, int quantite = 1);

    Carte* getCarte(int numCarte);


private:
    int m_nbJoueur;
    std::vector<Joueur> m_joueurs;

    Phase* m_phaseActuelle;

    std::map<Carte*, int> m_cartesPlateau;//cartes pas encore achetée
    std::vector<Carte*> v_cartesPlateau; // pour la gestion des cartes par numero

    ///Methode initialisation en debut de partie
    void initCartesPlateau();
    void initJoueur(Joueur& joueur);


    ///
    void changementDePhase();

};


#endif //DOMI_JEU_H
