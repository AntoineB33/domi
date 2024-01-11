#ifndef DOMI_JOUEUR_H
#define DOMI_JOUEUR_H


#include <map>
#include <list>
#include <string>

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


    ///////////////////////////////////////TOUR D UN JOUEUR
    void tourJoueur(Jeu &jeu);

    ///////////////////////////////////////ACTION DU JOUEUR (durant une phase ou via une carte)
    bool acheterCarte(Carte* c, Jeu& jeu);
    bool jouerCarteAction(Carte* c, Jeu& jeu);
    bool ajuster();
    ///////////////////////////////////////ACTION    void ajouterRetirerValeurSupp(int nbValeurSup);
    void recevoirCarte(Jeu& jeu, int coutMax);
    void ecarter(Jeu& jeu, int quantite);
    void supprimerCarteMain(Carte*,int);
    void addNbAchatPhase(int);
    void addNbActionPhase(int);
    void ajouterRetirerValeurSupp(int);


    //futures metohdes private , pour l'instant en public pour les tests
    void piocherCarteDeck(int quantite = 1); // quantite : nombre de carte a piocher
    bool defausserCarte(Carte*carte);
    bool defausserCarte();
    bool dansRebus(Carte *carte);
    bool mettreEncoursDutilisationCartes(Carte* carte, int quantite = 1);

private:
    std::map<Carte*,int> m_main;
    std::map<Carte*,int> m_carteEnCoursDutilisation;
    std::map<Carte*,int> m_deck;
    std::list<Carte*> m_defausse;
    std::list<Carte*> rebus;

    const int m_numJoueur;
    int m_nbAchatPossible;
    int m_nbActionPossible;
    int m_valeurSupp; //donner par les cartes comme : marché

    bool aGagner();
    int nbPointVictoire();

    int nbValeurDisponible() const;//calcul "l'argent" qui peut etre depensé
    bool peutAcheterCarte(Carte* carte, Jeu jeu);
    void prendreArgent(int valeur);
    bool mettreCarteDefausseDansDeck();


    ///////////////////////////////////////IHM TERMINAL
    std::string couleurJ;

    void jouerPhase(Jeu &jeu);
    void commandeHELP();
    void commandeSHOWME();
    Carte* demandeChercherCarte(std::map<Carte*,int> m, std::string &commande);
    int demandeQuantiteCarte(std::map<Carte*,int> m, Carte* c, std::string &commande);
    void commandeAchat(Jeu &jeu);
    void commandeJoueur(Jeu &Jeu);
    void commandeMettreCarteUtilisation();
    void faireAjustement(Jeu& jeu);
    void commandeDefausserCartes();





};


#endif //DOMI_JOUEUR_H
