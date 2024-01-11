#ifndef DOMI_ATELIER_H
#define DOMI_ATELIER_H

#include "Royaume.h"
#include <string>

class Atelier : public Royaume{
public:
    static Atelier* makeAtelier();
    virtual ~Atelier();


private :
    Atelier(std::string nom, int cout,std::string description);
    static Atelier* instanceAtelier;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Atelier_H
