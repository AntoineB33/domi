#ifndef DOMI_DUCHE_H
#define DOMI_DUCHE_H


#include "Victoire.h"

class Duche : public Victoire {
public :
    static Duche* makeDuche();
    virtual ~Duche();

    Duche(Duche &duche) = delete;
    void operator=(const Duche&) = delete;

private :
    Duche(std::string, int, int);
    static Duche* instanceDuche;
};

#endif //DOMI_DUCHE_H
