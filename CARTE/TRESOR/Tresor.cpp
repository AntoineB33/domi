#include "Tresor.h"

#include <iostream>


Tresor::Tresor(std::string nom, int cout,int val): Carte(nom,TypeTresor, cout){
    m_valeur = val;
}
Tresor::~Tresor() {

}

int Tresor::getValeur() const {return m_valeur;}