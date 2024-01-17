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

    int getNbJoueur();
    Joueur* getJoueur(int i) ;
    const std::string* getNomPhaseActu() const;

    std::list<Carte*> getToutesLesCartes() const;

    bool commandePartieEstFinie();
    bool estFini() const;
    void setFini(bool);

    void afficherCartesPlateau();

    bool carteDisponible(Carte* carte);//si elle peut etre encore achetée
    bool retirerCarteDisponible(Carte* carte, int quantite = 1);
    void mettreDansRebus(Carte *carte);
    void ajoutCartesDefausses(Carte* carte, int quantite = 1);

    bool estAPhaseAction();
    bool estAPhaseAchat();

    Carte* demandeCartePlateau(Joueur& joueur, std::string& commande);



    void changementDePhase();
    void commandeGODMODE(std::vector<std::pair<Carte*, int>>& m);
    bool estAPhaseAjustement();
    // void initJoueurPhase(Joueur& joueur);
    //futur private

    //LANCEMENT

    void lancementJeu();


private:
    int m_nbJoueur;
    std::vector<Joueur> m_joueurs;
    bool m_fini; //bool pour savoir si la partie est fini, permet d'eviter de dupliquer les calculs
    std::vector<std::pair<Carte*, int>> reserve;
    std::list<Carte*> rebus;
    std::list<Carte*> allInstancesCards;

    void tour(int numJoueur = 0);//int numJoueur permet de reprendre la partie depuis l'enregistrement

    ///Methode initialisation en debut de partie
    void initCartesPlateau();
    void initJoueur(Joueur&);

    bool partieEstFinie();
    int getGagnant();



    ///


};


#endif //DOMI_JEU_H
