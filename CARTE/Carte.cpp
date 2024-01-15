#include "Carte.h"

#include <iostream>

#include <string>

#include "Jeu.h"
#include "Joueur.h"

#include "../case_insensitive_compare.h"

Carte::Carte(std::string nom, TypeCarte typeCarte,int cout) :m_nom(nom), m_type(typeCarte),m_cout(cout){
    description = "(Cout: " + std::to_string(cout) + ")\n";
}

Carte::~Carte(){

}

///GETTERS
std::string& Carte::getDesc() {
    return description;
}


bool Carte::operator<(const Carte& autre) const {//pour map
    if(m_type != autre.m_type){
        return m_type < autre.m_type;
    }
    else if (m_nom != autre.m_nom) {
        return m_nom < autre.m_nom;
    }
    return m_cout < autre.m_cout;
}

std::ostream& operator<<(std::ostream& os, const Carte& carte) {
    os << "Nom: " << carte.m_nom << ", Cout: " << carte.m_cout;
    return os;
}




std::string Carte::getNom() const{
    return m_nom;
}
int Carte::getTypeCarte() const{
    return m_type;
}
int Carte::getCout() const{
    return m_cout;
}




int Carte::getPointDeVictoire() const{
    return 0;
}


int Carte::getValeur() const{
    return 0;
}


void Carte::jouerAction(Joueur &joueur, Jeu &jeu) {
    (void)joueur;
    (void)jeu;
}









bool Carte::ajoutSuppCarte(std::list<Carte*>& l, Carte* c, int quantite) {
    if(quantite > 0){
        for(int i = 0; i < quantite; i++){
            l.push_back(c);
        }
    }
    else{
        int i = 0;
        while( i < quantite &&  !l.empty()){
            l.pop_back();
        }
    }
    return true;
}

bool Carte::ajoutSuppCarte(std::map<Carte*, int>& m, Carte* c, int quantite){
    auto it = m.find(c);
    if( quantite > 0){
        if (it != m.end()) {
            it->second += quantite;
            return true;
        }
        m.insert(std::pair<Carte*, int>(c, quantite));
        return true;
    }
    if(it == m.end()){
        return false;
    }
    int q = quantite + (it -> second);
    if(q > 0) {
        it->second = q;
    }
    else if (q == 0) {
        m.erase(it);
    }
    else{
        return false;//trop de carte à supprimer
    }
    return true;
}

Carte* Carte::chercherCarte(std::string mot, std::map<Carte*, int> m){
    for(auto entry : m){
        if(caseInsensitiveCompare(mot, entry.first->getNom())){//case insensitive compare
            return entry.first;
        }
    }
    return nullptr;
}

void Carte::afficher(std::map<Carte *, int> &m) {
    for (const auto& entry : m) {
        std::cout<< "   " << *(entry.first) << ": " << entry.second << "\n";
    }
}
