#include "Joueur.h"
#include "Jeu.h"

#include <random>

#include <iostream>
#include <ostream>
#include <algorithm>


Joueur::Joueur(const int numJoueur) :m_numJoueur(numJoueur), m_nbAchatPossible(0), m_nbActionPossible(0) , m_valeurSupp(0){

}

Joueur::~Joueur() {
    /*
    for (Carte* carte : m_deck) {
        delete carte;
    }
     */
/*
    for (auto& it : m_deck) {
        delete it.first;
    }
    std::cout<<"SUPP JOUEUR 1.2\n";
    for (Carte* carte : m_defausse) {
        delete carte;
    }
    std::cout<<"SUPP JOUEUR 1.3\n";
    for (auto& it : m_main) {
        delete it.first;
    }
    std::cout<<"SUPP JOUEUR 1.4\n";
    for (auto& it: m_carteEnCoursDutilisation) {
        delete it.first;
    }*/

    m_deck.clear();
    m_defausse.clear();
    m_main.clear();
    m_carteEnCoursDutilisation.clear();

}

void Joueur::nop(){}

std::ostream& operator<<(std::ostream& os, const Joueur& joueur) {
    os << "====================> Joueur " << joueur.m_numJoueur << ":\n";
    os << "nb achat restant : " << joueur.m_nbAchatPossible << "\t";
    os << "nb action restant : " << joueur.m_nbActionPossible << "\n";

    os << "Main:\n";
    for (const auto& entry : joueur.m_main) {
        os << "   " << *(entry.first) << ": " << entry.second << "\n";
    }

    os << "Cartes en cours d'utilisation:\n";
    for (const auto& entry : joueur.m_carteEnCoursDutilisation) {
        os << "   " << *(entry.first) << ": " << entry.second << "\n";
    }

    os << "Deck:\n";
    for (const auto& entry : joueur.m_deck) {
        os << "   " << *(entry.first) << ": " << entry.second << "\n";
    }

    os << "Défausse:\n";
    for (const auto& carte : joueur.m_defausse) {
        os << "   " << *carte << "\n";
    }
    return os;
}






void Joueur::initJoueur(int nbAchatNEW, int nbActionNEW){
    m_nbAchatPossible= nbAchatNEW;
    m_nbActionPossible = nbActionNEW;
    m_valeurSupp = 0;
}

//GETTERS
const std::map<Carte*, int>& Joueur::getMain() const {
    return m_main;
}

const std::map<Carte*, int>& Joueur::getCarteEnCoursDutilisation() const {
    return m_carteEnCoursDutilisation;
}

const std::map<Carte*,int>& Joueur::getDeck() const {
    return m_deck;
}

const std::list<Carte*>& Joueur::getDefausse() const {
    return m_defausse;
}

//GESTIONS DES CARTES
void Joueur::prendreCartePlateau(Carte* carte, Jeu& jeu,int quantite,bool gratuit) {
    if(!gratuit){
        prendreArgent(carte -> getCout());
    }
    Carte::ajoutSuppCarte(m_deck, carte, quantite);
    jeu.retirerCarteDisponible(carte, quantite);
}

///////////////////////////////////////ACTION DU JOUEUR
void Joueur::acheterCarte(Carte* carte, Jeu& jeu){
    if(peutAcheterCarte(carte, jeu)) {
        prendreCartePlateau(carte, jeu);
    }
}
void Joueur::jouerCarteAction(Carte* c, Jeu& jeu){
    if( c -> getTypeCarte() == TypeRoyaume){
        c -> jouerAction(*this, jeu);
    }
}

///////////////////////////////////////ACTION DU JOUEUR VIA UNE CARTE ACTION
void Joueur::supprimerCarteMain(Carte* c, int quantite){
    Carte::ajoutSuppCarte(m_main, c,-quantite);
}
void Joueur::addNbAchatPhase(int nbAchatPossible) {
    m_nbAchatPossible += nbAchatPossible;
}
void Joueur::addNbActionPhase(int nbActionPossible) {
    m_nbActionPossible += nbActionPossible;
}
void Joueur::ajouterRetirerValeurSupp(int nbValeurSup) {
    m_valeurSupp += nbValeurSup;
}
void Joueur::recevoirCarte(Jeu &jeu, int nbValeurSup) {
    std::cout<<"Recevez une carte coutant jusqu'à " << nbValeurSup << ".\n";
    int carteNum = 0;
    std::cin >> carteNum;
    prendreCartePlateau(jeu.getCarte(carteNum), jeu, 1, true);
}
void Joueur::defausserInfin(Jeu &jeu, int nbValeurSup) {
}










///////////////////////////////////////FONCTION PRIVATE

int Joueur::nbValeurDisponible() const {
    int val = m_valeurSupp;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        val += entry.second * (entry.first -> getValeur());
    }
    return val;
}
bool Joueur::peutAcheterCarte(Carte* carte, Jeu jeu){
    // il faut que le carte soit encore disponible a l'achat
    // que le joueur est l'argent necessaire
    // que le joueur est au moins un point d'achat
    return jeu.carteDisponible(carte) && nbValeurDisponible() > carte -> getCout() && m_nbAchatPossible > 0;
}
void Joueur::prendreArgent(int valeur) {
    int nb = nbValeurDisponible();
    //fond suffisant ?
    if(nb < valeur){
        return;
    }

    //valeur supp donné par carte action (ex: marché)
    if( valeur - m_valeurSupp <= 0 ){
        m_valeurSupp -= valeur;
        return;
    }
    else{
        valeur -= m_valeurSupp;
    }

    std::vector<std::pair<Carte*, int>> cartes;
    for (auto entry : m_carteEnCoursDutilisation) {
        if(entry.first -> getTypeCarte() == TypeTresor){
            cartes.push_back(std::make_pair(entry.first, entry.second));
        }
    }
    //cas specifique
    if(nb == valeur){
        for (auto entry : cartes ){
            Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, entry.first, - entry.second);
            Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
        }
        return;
    }
    std::sort(cartes.begin(), cartes.end(), [](const auto& a, const auto& b) {
        return a.first->getValeur() > b.first->getValeur();
    });
    // Parcours les cartes triees et retire la quantite necessaire pour atteindre la valeur voulue
    for (const auto& carte : cartes) {
        int quantiteRetiree = std::min(carte.first->getValeur(), carte.second);
        valeur -= quantiteRetiree * carte.first->getValeur();
        m_carteEnCoursDutilisation[carte.first] -= quantiteRetiree;

        Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte.first, -1);
        Carte::ajoutSuppCarte(m_defausse, carte.first, 1);
        if (valeur == 0) {
            break;// on sort
        }
    }
}

void Joueur::piocherCarteDeck(int quantite){
    //calcul nombre de carte dans le deck
    int nbCartes = 0;
    for (const auto& paire : m_deck) {
        nbCartes += paire.second;
    }
    //pioche carte
    while(quantite > 0 && nbCartes > 0){
        //aleatoire
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, nbCartes);
        int choixAleatoire = distrib(gen) ;

        //recherche de la carte
        for (auto& entry : m_deck) {
            choixAleatoire -= entry.second;
            if (choixAleatoire <= 0) { // carte trouvee donc on rajoute à la main
                Carte::ajoutSuppCarte(m_deck,entry.first, -1);
                Carte::ajoutSuppCarte(m_main,entry.first, 1);
                quantite -= 1;
                nbCartes -= 1;
                break;
            }
        }
    }
    if(quantite !=0){
        //PB
    }

}


void Joueur::defausserCarte(Carte* carte) {
    if(Carte::ajoutSuppCarte(m_main, carte, -1)){
        Carte::ajoutSuppCarte(m_defausse, carte, 1);
    }
}
void Joueur::defausserCarte() {
    for(auto entry : m_main){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_main.clear();
    for(auto entry : m_carteEnCoursDutilisation){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_carteEnCoursDutilisation.clear();
}
void Joueur::mettreDefausseDansDeck(){
    for(Carte* c : m_defausse){
        Carte::ajoutSuppCarte(m_deck, c, 1);
    }
    m_defausse.clear();
}
void Joueur::mettreEncoursDutilisationCartes(Carte* carte, int quantite) {
    if(Carte::ajoutSuppCarte(m_main, carte, -quantite)){
        Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte, quantite);
    }
}

