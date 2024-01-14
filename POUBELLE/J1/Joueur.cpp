#include "Joueur.h"
#include "Carte.h"
#include <iostream>

Joueur::Joueur(const int numJoueur) :m_numJoueur(numJoueur), m_nbAchatPhase(0), m_nbActionPhase(0) {

}

Joueur::~Joueur() {
    for (Carte* carte : m_deck) {
        delete carte;
    }
    for (Carte* carte : m_defausse) {
        delete carte;
    }

    for (auto& it : m_main) {
        delete it.first;
    }
    for (auto& it: m_carteEnCoursDutilisation) {
        delete it.first;
    }

    m_deck.clear();
    m_defausse.clear();
    m_main.clear();
    m_carteEnCoursDutilisation.clear();
}

std::ostream& operator<<(std::ostream& os, const Joueur& joueur) {
    os << "====================> Joueur " << joueur.m_numJoueur << ":\n";
    os << "nb achat restant : " << joueur.m_nbAchatPhase << "\t";
    os << "nb action restant : " << joueur.m_nbActionPhase << "\n";

    os << "Main:\n";
    for (const auto& entry : joueur.m_main) {
        os << "   " << *(entry.first) << ": " << entry.second << "\n";
    }

    os << "Cartes en cours d'utilisation:\n";
    for (const auto& entry : joueur.m_carteEnCoursDutilisation) {
        os << "   " << *(entry.first) << ": " << entry.second << "\n";
    }

    os << "Deck:\n";
    for (const auto& carte : joueur.m_deck) {
        os << "   " << *carte << "\n";
    }

    os << "Défausse:\n";
    for (const auto& carte : joueur.m_defausse) {
        os << "   " << *carte << "\n";
    }
    return os;
}




void Joueur::addNbAchatPhase(int nbAchatPhase) {
    m_nbAchatPhase += nbAchatPhase;
}
void Joueur::addNbActionPhase(int nbActionPhase) {
    m_nbActionPhase += nbActionPhase;
}
void Joueur::initJoueur(int nbAchatNEW, int nbActionNEW){
    m_nbAchatPhase = nbAchatNEW;
    m_nbActionPhase = nbActionNEW;
}

//GETTERS
const std::map<Carte*, int>& Joueur::getMain() const {
    return m_main;
}

const std::map<Carte*, int>& Joueur::getCarteEnCoursDutilisation() const {
    return m_carteEnCoursDutilisation;
}

const std::list<Carte*>& Joueur::getDeck() const {
    return m_deck;
}

const std::list<Carte*>& Joueur::getDefausse() const {
    return m_defausse;
}

//GESTIONS DES CARTES

int Joueur::supprimerCarteMain(Carte* c, int quantite){
    return Carte::supprimerCarte(m_main, c,quantite);
}
