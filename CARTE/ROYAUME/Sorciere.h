#ifndef DOMI_SORCIERE_H
#define DOMI_SORCIERE_H

#include "Royaume.h"
#include <string>

class Sorciere : public Royaume{
public:
    static Sorciere* makeSorciere();
    virtual ~Sorciere();


private :
    Sorciere(std::string nom, int cout,std::string description);
    static Sorciere* instanceSorciere;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Sorciere_H
