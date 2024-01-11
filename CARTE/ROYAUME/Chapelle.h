#ifndef DOMI_CHAPELLE_H
#define DOMI_CHAPELLE_H

#include "Royaume.h"
#include <string>

class Chapelle : public Royaume{
public:
    static Chapelle* makeChapelle();
    virtual ~Chapelle();


private :
    Chapelle(std::string nom, int cout,std::string description);
    static Chapelle* instanceChapelle;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Chapelle_H
