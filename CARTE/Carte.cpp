#include "Carte.h"

#include <iostream>

#include <string>

#include "Jeu.h"
#include "Joueur.h"
#include "case_insensitive_compare.h"
#include "CouleurTerminal.h"

Carte::Carte(std::string nom, TypeCarte typeCarte,int cout) :
    m_description("(Cout: " + std::to_string(cout) + ")\n"), m_nom(nom),
    m_type(typeCarte), m_cout(cout) {
}

Carte::~Carte(){

}

///GETTERS
std::string& Carte::getDesc() {
    return m_description;
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









void Carte::ajoutSuppCarte(std::list<Carte*>& l, Carte* c, int quantite) {
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
    return;
}

void Carte::ajoutSuppCarte(std::vector<std::pair<Carte*, int>>& li, Carte* c, int quantite, bool canErase){
    for(long unsigned int i = 0; i<li.size(); i++){
        if(li[i].first == c){
            if(quantite > 0){
                li[i].second += quantite;
            }
            else{
                int q = quantite + li[i].second;
                if(q > 0 || (q==0 && !canErase)) {
                    li[i].second = q;
                }
                else if (q == 0) {
                    li.erase(li.begin() + i);
                }
            }
            return;
        }
    }
    if(quantite > 0){
        li.push_back(std::make_pair(c, quantite));
    }
}

Carte* Carte::chercherCarte(std::string mot, std::vector<std::pair<Carte*, int>> li){
    try {
        long unsigned int place = std::stoi(mot);
        if(place >= li.size()){
            return nullptr;
        }
    } catch (std::exception& e) {
        for(auto entry : li){
            if(caseInsensitiveCompare(mot, entry.first->getNom())) {
                return entry.first;
            }
        }
    }
    return nullptr;
}

void Carte::afficher(const std::vector<std::pair<Carte *, int>> &li, bool (*condition)(Carte *)) {
    for(long unsigned int i = 0; i<li.size(); i++){
        if(condition(li[i].first)){
            std::cout << "-> ";
        } else {
            std::cout << "   ";
        }
        std::cout << li[i].second << " ";
        afficherCarteEtDesc(li[i].first);
    }
}

void Carte::afficherCarteEtDesc(Carte* c) {
    std::cout << c->getNom() << " ";
    std::cout <<DIM_TEXT<<GRAY<< c->getDesc() << "\n" << RESET;
}