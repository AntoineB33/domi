#ifndef DOMI_JOUEUR_H
#define DOMI_JOUEUR_H

#include "Carte.h"
#include <map>
#include <list>


class Joueur {
public:
    Joueur (int numJouer);
    ~Joueur();

    friend std::ostream& operator<<(std::ostream& os, const Joueur& joueur);


    void addNbAchatPhase(int nbAchatPhase);
    void addNbActionPhase(int nbActionPhase);
    void initJoueur(int nbAchatNEW, int nbActionNEW);

    //GETTERS
    const std::map<Carte*,int>& getMain() const;
    const std::map<Carte*,int>& getCarteEnCoursDutilisation() const;
    const std::list<Carte*>& getDeck() const;
    const std::list<Carte*>& getDefausse() const;

    //GESTIONS DES CARTES
    int supprimerCarteMain(Carte* c, int quantite = 1);

private:
    std::map<Carte*,int> m_main;
    std::map<Carte*,int> m_carteEnCoursDutilisation;
    std::list<Carte*> m_deck;
    std::list<Carte*> m_defausse;

    const int m_numJoueur;
    int m_nbAchatPhase;
    int m_nbActionPhase;

};


#endif //DOMI_JOUEUR_H
