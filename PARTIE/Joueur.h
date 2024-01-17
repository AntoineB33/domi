#ifndef DOMI_JOUEUR_H
#define DOMI_JOUEUR_H


#include <map>
#include <list>
#include <string>

#include "Carte.h"

class Jeu;
class Phase;

class Joueur {
public:
    Joueur (int numJouer);
    ~Joueur();

    bool m_godMode = false;

    friend std::ostream& operator<<(std::ostream& os, const Joueur& joueur);


    //GETTERS
    const std::vector<std::pair<Carte*, int>>& getMain() const;
    const std::vector<std::pair<Carte*, int>>& getCarteEnCoursDutilisation() const;
    const std::vector<std::pair<Carte*, int>>& getDeck() const;
    const std::vector<std::pair<Carte*, int>>& getDefausse() const;
    int getNbAction() const;
    int getNbAchat() const;
    int getId() const;
    bool typeDansMain(TypeCarte type) const;
    // bool isInGodMode();

    //GESTIONS DES CARTES
    void mainVersUtilise(Carte* c);
    void reserveVersMain(Jeu& jeu, Carte* carte, int quantite);

    bool prendreCartePlateau(Jeu& jeu, Carte* carte, int quantite = 1, bool gratuit = false); // le booleen permet la destribution en debut de parti
    int getVictoireDansDeck();


    ///////////////////////////////////////TOUR D UN JOUEUR
    void tourJoueur(Jeu &jeu);

    ///////////////////////////////////////ACTION DU JOUEUR (durant une phase ou via une carte)
    bool acheterCarte(Jeu& jeu, Carte* c);
    bool jouerCarteAction(Jeu& jeu, Carte* c);
    bool ajuster();
    ///////////////////////////////////////ACTION    void ajouterRetirerValeurSupp(int nbValeurSup);
    bool recevoirCartePlateau(Jeu& jeu, Carte* carte,int coutMax);
    void ecarter(Jeu& jeu, Carte*, int quantite);
    void defaussPiocher();
    void addNbAchatPhase(int);
    void addNbActionPhase(int);
    void ajouterRetirerValeurSupp(int);
    void augmenterTresor(Jeu&, int);


    //futures metohdes private , pour l'instant en public pour les tests
    std::list<Carte*> piocherCarteDeck(int quantite = 1); // quantite : nombre de carte a piocher
    bool defausserCarte(Carte*carte);
    bool defausserCarte();
    bool mettreDansRebus(Jeu& jeu, Carte *carte);
    bool mettreEncoursDutilisationCartes(Carte* carte, int quantite = 1);



    ///////////////////////////////////////IHM TERMINAL
    std::list<Carte*> commandeEcarter(Jeu& jeu, int quantite);
    Carte* demandeChercherCarte(const std::vector<std::pair<Carte*, int>>& li, std::string &commande) const;
    bool commandePiocherCarteDeck(int quantite = 1);
    void afficherMain();
    void afficherUtilise();

private:
    std::vector<std::pair<Carte*, int>> m_main;
    std::vector<std::pair<Carte*, int>> m_carteEnCoursDutilisation;
    std::vector<std::pair<Carte*, int>> m_deck;
    std::vector<std::pair<Carte*, int>> m_defausse;
    Phase* m_phaseActuelle;

    const int m_numJoueur;
    int m_nbAchatPossible;
    int m_nbActionPossible;
    int m_valeurSupp; //donner par les cartes comme : marché

    int nbPointVictoire();

    int nbValeurDisponible() const;//calcul "l'argent" qui peut etre depensé
    bool peutAcheterCarte(Carte* carte, Jeu& jeu);
    bool prendreArgent(int valeur);
    bool mettreCarteDefausseDansDeck();


    ///////////////////////////////////////IHM TERMINAL
    std::string couleurJ;


    void commandeHELP();
    void commandeSHOWME();
    int demandeQuantiteCarte(std::map<Carte*,int>& m, Carte* c, std::string &commande);

    void commandeAchat(Jeu &jeu);
    void commandeAction(Jeu &Jeu);
    void commandeMettreCarteUtilisation();
    void commandeGODMODE(Jeu& jeu);
    void faireAjustement(Jeu& jeu);
    void commandeDefausserCartes();





};


#endif //DOMI_JOUEUR_H
