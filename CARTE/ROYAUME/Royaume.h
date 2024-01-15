#ifndef DOMI_ROYAUME_H
#define DOMI_ROYAUME_H

#include "Carte.h"
#include "Joueur.h"
#include "Jeu.h"
#include <string>

class Royaume : public Carte{
public:
    Royaume(std::string nom, int cout,std::string description);
    ~Royaume();

    std::string& getDesc() const override;
    std::string getDescription() const;

    friend std::ostream& operator<<(std::ostream& os, const Royaume& royaume);
    void jouerAction(Joueur& joueur, Jeu& jeu) override;



protected:
    //méthodes utiles pour les classes filles
    void ajoutAction(Joueur & joueur, int nb);
    void ajoutAchat(Joueur & joueur, int nb);
    void ajouterValeurSupp(Joueur & joueur, int nbValeurSupp);


    ///////////////IHM

    void commandeRecevoirCartePlateau(Joueur& joueur, Jeu& jeu, int coutMax);


private:
    std::string m_description;
    virtual void faireAction(Joueur& joueur, Jeu& jeu) = 0;



};


#endif //DOMI_ROYAUME_H
