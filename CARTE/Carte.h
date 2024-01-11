#ifndef PROJETCARTE_CARTE_H
#define PROJETCARTE_CARTE_H

#include <string>
#include <map>
#include <list>



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

    friend std::ostream& operator<<(std::ostream& os, const Carte& carte);

    int getTypeCarte() const;
    int getCout() const;
    std::string getNom();

    //fonction pour certain type de carte
    virtual int getPointDeVictoire() const;
    virtual int getValeur() const;
    virtual void jouerAction(Joueur& joueur, Jeu& jeu) ;



    //methode utile pour d'autre classe
    static bool ajoutSuppCarte(std::list<Carte*>& l, Carte* c, int  quantite = 1);//ne supprime qque les derniere carte
    static bool ajoutSuppCarte(std::map<Carte*, int>& m, Carte* c, int quantite = 1);
    static Carte* chercherCarte(std::string, std::map<Carte*, int> m);
    static void afficher(std::map<Carte*, int> m);


private:
    std::string  m_nom;
    TypeCarte m_type;
    int m_cout;









};


#endif
