#ifndef DOMI_MINE_H
#define DOMI_MINE_H

#include "Royaume.h"
#include <string>

class Mine : public Royaume{
public:
    static Mine* makeMine();
    virtual ~Mine();


private :
    Mine(std::string nom, int cout,std::string description);
    static Mine* instanceMine;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Mine_H
