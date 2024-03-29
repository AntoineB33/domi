#include "Duche.h"

Duche* Duche::instanceDuche = new Duche("Duche", 5, 3);

Duche* Duche::makeDuche() {
    return instanceDuche;
}

Duche::~Duche() {
    delete Duche::instanceDuche;
}

Duche::Duche(std::string nom, int cout, int point) : Victoire(nom, cout, point) {}

std::ostream& operator<<(std::ostream& os, const Duche& duche) {
    os << reinterpret_cast<const Victoire&>(duche);
    return os;
}