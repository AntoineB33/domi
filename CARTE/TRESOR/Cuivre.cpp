#include "Cuivre.h"

Cuivre* Cuivre::instanceCuivre = new Cuivre("Cuivre", 0, 1);

Cuivre* Cuivre::makeCuivre() {
    return instanceCuivre;
}
Carte* Cuivre::getCarte(){
    return instanceCuivre;
}

Cuivre::~Cuivre() {
    delete instanceCuivre;
}

Cuivre::Cuivre(std::string nom, int cout, int val) : Tresor(nom, cout, val) {}

std::ostream& operator<<(std::ostream& os, const Cuivre& cuivre) {
    os << reinterpret_cast<const Tresor&>(cuivre);
    return os;
}