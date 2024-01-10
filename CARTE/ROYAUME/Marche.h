#ifndef DOMI_MARCHE_H
#define DOMI_MARCHE_H

#include "Royaume.h"
#include <string>

class Marche : public Royaume{
public:
    static Marche* makeMarche();
    virtual ~Marche();


private :
    Marche(std::string nom, int cout,std::string description);
    static Marche* instanceMarche;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_MARCHE_H
