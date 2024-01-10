//
// Created by moi on 22/12/23.
//

#include "Domaine.h"


Domaine* Domaine::instanceDomaine = new Domaine("Domaine",2,1);

Domaine* Domaine::makeDomaine() {
    return instanceDomaine;
}
Domaine::~Domaine() {
    delete Domaine::instanceDomaine;
}

Domaine::Domaine(std::string nom, int cout, int point): Victoire(nom,cout,point){}

std::ostream& operator<<(std::ostream& os, const Domaine& domaine) {
    os << reinterpret_cast<const Victoire&>(domaine);
    return os;
}


