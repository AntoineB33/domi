#ifndef DOMI_JOUEUR_H
#define DOMI_JOUEUR_H



#include "Carte.h"

class Jeu;
class Phase;

class Joueur {
public:
    Joueur (Jeu& jeu, int numJouer);
    ~Joueur();

    bool m_godMode = false;

    //GETTERS
    const std::vector<std::pair<Carte*, int>>& getMain() const;
    const std::vector<std::pair<Carte*, int>>& getCarteEnCoursDutilisation() const;
    const std::vector<std::pair<Carte*, int>>& getDefausse() const;
    int getNbAction() const;
    int getNbAchat() const;
    int getId() const;
    bool typeDansMain(TypeCarte type) const;
    int nbValeurDisponible() const;//calcul "l'argent" qui peut etre depensé
    bool isInGodMode();

    //GESTIONS DES CARTES
    void mainVersUtilise(Carte* c);
    void reserveVersMain(Carte* carte, int quantite = 1);
    void mettreMainDansDefausse();

    bool reserveVersDeck(Jeu& jeu, Carte* carte, int quantite = 1, bool gratuit = false); // le booleen permet la destribution en debut de parti
    int getVictoireDansDeck();
    void mettreUtiliseDansDefausse();
    void mainVersDeck(Carte* carte, int quantite = 1);


    void tourJoueur(Jeu &jeu);

    void ecarter(Jeu& jeu, Carte* carte, int quantite = 1);
    void defaussPiocher();
    void addNbAchatPhase(int);
    void addNbActionPhase(int);
    void ajouterRetirerValeurSupp(int);
    void commandeRecevoirCartePlateau(int coutMax, bool versDefausse = true);
    void reserveVersDefausse(Carte* carte, int quantite = 1);

    void defausserCarte(Carte*carte);
    void mettreEncoursDutilisationCartes(Carte* carte, int quantite = 1);




    ///////////////////////////////////////IHM TERMINAL
    Carte* demandeChercherCarte(std::vector<std::pair<Carte *, int>> li, std::string &commande, int& idCarte);
    void afficherMain(bool pourPrendre = false, std::function<bool(Carte*)> condition = [](Carte*) { return false; }, int start = 0);
    void afficherUtilise();
    void augmenterTresor(Jeu&, int);
    void jouerRenovation(int quantite = 1);
    void demandeEcarter(int quantite = 1);
    void piocher(int quantite = 1);
private:
    std::vector<std::pair<Carte*, int>> m_main;
    std::vector<std::pair<Carte*, int>> m_carteEnCoursDutilisation;
    std::vector<std::pair<Carte*, int>> m_deck;
    std::vector<std::pair<Carte*, int>> m_defausse;
    Phase* m_phaseActuelle;
    Jeu& jeu;

    const int m_numJoueur;
    int m_nbAchatPossible;
    int m_nbActionPossible;
    int m_valeurSupp; //donner par les cartes comme : marché

    void prendreArgent(int valeur);


    ///////////////////////////////////////IHM TERMINAL
    std::string couleurJ;


    void commandeHELP();
    // void commandeSHOWME();
    // int demandeQuantiteCarte(std::map<Carte*,int>& m, Carte* c, std::string &commande);


    
    void mettreDefausseDansDeck();





};


#endif //DOMI_JOUEUR_H
