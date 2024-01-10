//
// Created by moi on 22/12/23.
//

#ifndef DOMI_DUCHE_H
#define DOMI_DUCHE_H


#include "Victoire.h"

class Duche : public Victoire {
public :
    static Duche* makeDuche();
    virtual ~Duche();
    friend std::ostream& operator<<(std::ostream& os, const Duche& duche);

    Duche(Duche &duche) = delete;
    void operator=(const Duche&) = delete;

private :
    Duche(std::string, int, int);
    static Duche* instanceDuche;
};

#endif //DOMI_DUCHE_H
