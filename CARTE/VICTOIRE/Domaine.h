#ifndef DOMI_DOMAINE_H
#define DOMI_DOMAINE_H

#include "Victoire.h"

class Domaine : public Victoire {
public :
    static Domaine* makeDomaine();
    virtual ~Domaine();

    Domaine(Domaine &domaine) = delete;
    void operator=(const Domaine&) = delete;

private :
    Domaine(std::string, int, int);
    static Domaine* instanceDomaine;
};

#endif //DOMI_DOMAINE_H
