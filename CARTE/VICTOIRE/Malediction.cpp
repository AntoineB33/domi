#include "Malediction.h"

Malediction* Malediction::instanceMalediction = new Malediction("Malediction", 0, -1);

Malediction* Malediction::makeMalediction() {
    return instanceMalediction;
}

Malediction::~Malediction() {
    delete Malediction::instanceMalediction;
}

Malediction::Malediction(std::string nom, int cout, int point) : Victoire(nom, cout, point) {}

std::ostream& operator<<(std::ostream& os, const Malediction& malediction) {
    os << reinterpret_cast<const Victoire&>(malediction);
    return os;
}