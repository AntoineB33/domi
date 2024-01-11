#ifndef DOMI_BUCHERON_H
#define DOMI_BUCHERON_H

#include "Royaume.h"
#include <string>

class Bucheron : public Royaume{
public:
    static Bucheron* makeBucheron();
    virtual ~Bucheron();


private :
    Bucheron(std::string nom, int cout,std::string description);
    static Bucheron* instanceBucheron;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Bucheron_H
