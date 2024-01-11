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
    const std::string* getNomPhaseActu() const;
    const std::map<Carte*, int> getCartesPlateau() const;

    bool getFini() const;
    void setFini(bool);

    void afficherCartesPlateau();

    bool carteDisponible(Carte* carte);//si elle peut etre encore achetée
    bool retirerCarteDisponible(Carte* carte, int quantite = 1);


    void changementDePhase();
    bool estAPhaseAjustement();
    void initJoueurPhase(Joueur& joueur);
    //futur private

    //LANCEMENT

    void lancementJeu();


private:
    int m_nbJoueur;
    std::vector<Joueur> m_joueurs;
    bool m_fini; //bool pour savoir si la partie est fini, permet d'eviter de dupliquer les calculs
    Phase* m_phaseActuelle;
    std::map<Carte*, int> m_cartesPlateau;//cartes pas encore achetée

    void tour(int numJoueur = 0);//int numJoueur permet de reprendre la partie depuis l'enregistrement

    ///Methode initialisation en debut de partie
    void initCartesPlateau();
    void initJoueur(Joueur&);




    ///


};


#endif //DOMI_JEU_H
