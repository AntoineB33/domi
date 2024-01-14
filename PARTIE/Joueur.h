#ifndef DOMI_JOUEUR_H
#define DOMI_JOUEUR_H


#include <map>
#include <list>

#include "Carte.h"

class Jeu;

class Joueur {
public:
    Joueur (int numJouer);
    ~Joueur();

    void nop();

    friend std::ostream& operator<<(std::ostream& os, const Joueur& joueur);



    void initJoueur(int nbAchatNEW, int nbActionNEW);

    //GETTERS
    const std::map<Carte*,int>& getMain() const;
    const std::map<Carte*,int>& getCarteEnCoursDutilisation() const;
    const std::map<Carte*, int>& getDeck() const;
    const std::list<Carte*>& getDefausse() const;

    //GESTIONS DES CARTES

    void prendreCartePlateau(Carte* carte, Jeu& jeu, int quantite = 1, bool gratuit = false); // le booleen permet la destribution en debut de parti

    ///////////////////////////////////////ACTION DU JOUEUR (durant une phase ou via une carte)
    void acheterCarte(Carte* c, Jeu& jeu);
    void jouerCarteAction(Carte* c, Jeu& jeu);
    ///////////////////////////////////////ACTION DU JOUEUR VIA UNE CARTE ACTION (via carte uniquement)
    void supprimerCarteMain(Carte* c, int quantite = 1);
    void addNbAchatPhase(int nbAchatPhase);
    void addNbActionPhase(int nbActionPhase);
    void ajouterRetirerValeurSupp(int nbValeurSup);

    //futures metohdes private , pour l'instant en public pour les tests
    void piocherCarteDeck(int quantite = 1); // quantite : nombre de carte a piocher
    void defausserCarte(Carte* carte);
    void defausserCarte();
    void mettreDefausseDansDeck();
    void mettreEncoursDutilisationCartes(Carte* carte, int quantite = 1);

private:
    std::map<Carte*,int> m_main;
    std::map<Carte*,int> m_carteEnCoursDutilisation;
    std::map<Carte*,int> m_deck;
    std::list<Carte*> m_defausse;

    const int m_numJoueur;
    int m_nbAchatPossible;
    int m_nbActionPossible;
    int m_valeurSupp; //donner par les cartes comme : marché


    int nbValeurDisponible() const;//calcul "l'argent" qui peut etre depensé
    bool peutAcheterCarte(Carte* carte, Jeu jeu);
    void prendreArgent(int valeur);



};


#endif //DOMI_JOUEUR_H
