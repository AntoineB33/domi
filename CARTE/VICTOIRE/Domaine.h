//
// Created by moi on 22/12/23.
//

#ifndef DOMI_DOMAINE_H
#define DOMI_DOMAINE_H

#include "Victoire.h"

class Domaine : public Victoire {
public :
    static Domaine* makeDomaine();
    virtual ~Domaine();
    // friend std::ostream& operator<<(std::ostream& os, const Domaine& domaine);

    Domaine(Domaine &domaine) = delete;
    void operator=(const Domaine&) = delete;

private :
    Domaine(std::string, int, int);
    static Domaine* instanceDomaine;
};

#endif //DOMI_DOMAINE_H
