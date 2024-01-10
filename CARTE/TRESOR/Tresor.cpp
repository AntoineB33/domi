#include "Tresor.h"

#include <iostream>


Tresor::Tresor(std::string nom, int cout,int val): Carte(nom,TypeTresor, cout){
    m_valeur = val;
}
Tresor::~Tresor() {

}

int Tresor::getValeur() const {return m_valeur;}


std::ostream& operator<<(std::ostream& os, const Tresor& tresor){
        os<< reinterpret_cast<const Carte&>(tresor)<<", valeur: "<<tresor.m_valeur;
        return os;
}