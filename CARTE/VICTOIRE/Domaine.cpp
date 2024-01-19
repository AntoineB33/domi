#include "Domaine.h"


Domaine* Domaine::instanceDomaine = new Domaine("Domaine",2,1);

Domaine* Domaine::makeDomaine() {
    return instanceDomaine;
}
Domaine::~Domaine() {
    delete Domaine::instanceDomaine;
}

Domaine::Domaine(std::string nom, int cout, int point): Victoire(nom,cout,point){}


