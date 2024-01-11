#ifndef DOMI_RENOVATION_H
#define DOMI_RENOVATION_H

#include "Royaume.h"
#include <string>

class Renovation : public Royaume{
public:
    static Renovation* makeRenovation();
    virtual ~Renovation();


private :
    Renovation(std::string nom, int cout,std::string description);
    static Renovation* instanceRenovation;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Renovation_H
