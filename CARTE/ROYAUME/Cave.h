#ifndef DOMI_CAVE_H
#define DOMI_CAVE_H

#include "Royaume.h"
#include <string>

class Cave : public Royaume{
public:
    static Cave* makeCave();
    virtual ~Cave();


private :
    Cave(std::string nom, int cout,std::string description);
    static Cave* instanceCave;

    void faireAction(Joueur& joueur, Jeu& jeu) override;
};


#endif //DOMI_Cave_H
