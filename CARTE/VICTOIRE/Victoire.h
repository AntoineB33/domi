#ifndef DOMI_VICTOIRE_H
#define DOMI_VICTOIRE_H

#include "Carte.h"
#include <string>

class Victoire : public Carte
        {
public:
    Victoire(std::string, int, int);
    ~Victoire();
    int getPointDeVictoire() const override ;


private:
    int m_pointDeVictoire;
};


#endif //DOMI_VICTOIRE_H
