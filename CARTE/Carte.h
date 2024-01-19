#ifndef PROJETCARTE_CARTE_H
#define PROJETCARTE_CARTE_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include <functional>
#include "case_insensitive_compare.h"



class Joueur;
class Jeu;


enum TypeCarte{
    TypeRoyaume,
    TypeVictoire,
    TypeTresor,
};


class Carte
{
public:
    Carte(std::string,TypeCarte ,int);
    ~Carte();


    bool operator<(const Carte& autre) const;//utiliser pour le hachage dans map

    // friend std::ostream& operator<<(std::ostream& os, const Carte& carte);

    int getTypeCarte() const;
    int getCout() const;
    std::string getNom() const;
    virtual std::string& getDesc();

    //fonction pour certain type de carte
    virtual int getPointDeVictoire() const;
    virtual int getValeur() const;
    virtual void jouerAction(Joueur& joueur, Jeu& jeu) ;



    //methode utile pour d'autre classe
    // static void ajoutSuppCarte(std::list<Carte*>& l, Carte* c, int  quantite = 1);//ne supprime qque les derniere carte
    static void ajoutSuppCarte(std::vector<std::pair<Carte*, int>>& m, Carte* c, int quantite = 1, bool canErase = true);
    static Carte* chercherCarte(std::vector<std::pair<Carte*, int>> m, std::string commande, int& idCarte);
    static int afficher(const std::vector<std::pair<Carte *, int>> &li, bool pourPrendre = false, std::function<bool(Carte*)> condition = [](Carte*) { return false; }, int start = 0);
    static void afficherCarteEtDesc(Carte* c);

protected:
    std::string m_description;


private:
    const std::string  m_nom;
    TypeCarte m_type;
    int m_cout;

};


#endif
