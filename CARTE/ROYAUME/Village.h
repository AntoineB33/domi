#ifndef DOMI_VILLAGE_H
#define DOMI_VILLAGE_H

#include "Royaume.h"
#include <string>

class Village : public Royaume{
public:
    static Village* makeVillage();
    virtual ~Village();


private :
    Village(std::string nom, int cout,std::string description);
    static Village* instanceVillage;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Village_H
