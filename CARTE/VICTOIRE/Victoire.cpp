#include <iostream>
#include "Victoire.h"

Victoire::Victoire(std::string nom, int cout, int point): Carte(nom, TypeTresor,cout) {
    m_pointDeVictoire = point;
}
Victoire::~Victoire() {}

int Victoire::getPointDeVictoire() const {return m_pointDeVictoire;}
/*
std::ostream& operator<<(std::ostream& os, const Victoire& victoire){
    os<< reinterpret_cast<const Carte&>(victoire)<<", point de victoire: "<<victoire.m_pointDeVictoire;
    return os;
}
*/

// std::ostream& operator<<(std::ostream& os, const Victoire& victoire) {
//     os << reinterpret_cast<const Carte&>(victoire) << ", point de victoire: " << victoire.m_pointDeVictoire;
//     return os;
// }