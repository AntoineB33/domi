#include <iostream>
#include "Victoire.h"

Victoire::Victoire(std::string nom, int cout, int point): Carte(nom, TypeVictoire,cout) {
    m_pointDeVictoire = point;
}

Victoire::~Victoire() {}

int Victoire::getPointDeVictoire() const {return m_pointDeVictoire;}