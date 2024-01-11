#ifndef DOMI_FORGERON_H
#define DOMI_FORGERON_H

#include "Royaume.h"
#include <string>

class Forgeron : public Royaume{
public:
    static Forgeron* makeForgeron();
    virtual ~Forgeron();


private :
    Forgeron(std::string nom, int cout,std::string description);
    static Forgeron* instanceForgeron;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Forgeron_H
