//
// Created by moi on 22/12/23.
//

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

    friend std::ostream& operator<<(std::ostream& os, const Victoire& Victoire);


private:
    int m_pointDeVictoire;
};


#endif //DOMI_VICTOIRE_H
