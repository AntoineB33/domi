#include "Joueur.h"
#include "Jeu.h"
#include "Carte.h"
#include "Phase.h"
#include "PhaseAction.h"

#include <cstdlib>
#include <ctime>

#include <random>

#include <iostream>
#include <ostream>
#include <algorithm>
#include <functional>


#include "Atelier.h"
#include "Bucheron.h"
#include "Cave.h"
#include "Chapelle.h"
#include "Forgeron.h"
#include "Marche.h"
#include "Mine.h"
#include "Renovation.h"
#include "Sorciere.h"
#include "Village.h"

//POUR LES COULEURS DANS LE TERMINAL
#include "CouleurTerminal.h"

Joueur::Joueur(Jeu& jeu0, const int idJoueur) :jeu(jeu0), m_numJoueur(idJoueur) {
    couleurJ =  "\033["+std::to_string(m_numJoueur+33)+"m";
    m_phaseActuelle = &PhaseAction::getInstance();
}

Joueur::~Joueur() {
    m_deck.clear();
    m_defausse.clear();
    m_main.clear();
    m_carteEnCoursDutilisation.clear();

}

//GETTERS
const std::vector<std::pair<Carte*, int>>& Joueur::getMain() const {
    return m_main;
}

const std::vector<std::pair<Carte*, int>>& Joueur::getCarteEnCoursDutilisation() const {
    return m_carteEnCoursDutilisation;
}

const std::vector<std::pair<Carte*, int>> & Joueur::getDefausse() const {
    return m_defausse;
}

int Joueur::getNbAchat() const {
    return m_nbAchatPossible;
}

int Joueur::getNbAction() const {
    return m_nbActionPossible;
}

int Joueur::getId() const {
    return m_numJoueur;
}

bool Joueur::typeDansMain(TypeCarte type) const {
    for(std::pair<Carte*, int> carte : m_main){
        if(carte.first->getTypeCarte() == type){
            return true;
        }
    }
    return false;
}

//GESTIONS DES CARTES
bool Joueur::reserveVersDeck(Jeu& jeu, Carte* carte, int quantite, bool gratuit) {
    if(!gratuit){
        prendreArgent(quantite * (carte -> getCout()));
    }
    Carte::ajoutSuppCarte(m_deck, carte, quantite);
    jeu.retirerDeReserve(carte);
    return true;
}

int Joueur::getVictoireDansDeck(){
    int nb = 0;
    for(auto c : m_deck){
        if(c.first -> getTypeCarte() == TypeVictoire){
            nb += c.first -> getPointDeVictoire();
        }
    }
    return nb;
}

///////////////////////////////////////ACTION DU JOUEUR VIA UNE CARTE ACTION
void Joueur::reserveVersMain(Carte* carte, int quantite) {
    jeu.retirerDeReserve(carte, quantite);
    Carte::ajoutSuppCarte(m_main, carte, -quantite);
}

void Joueur::ecarter(Jeu& jeu, Carte* carte, int quantite){
    Carte::ajoutSuppCarte(m_main, carte, -quantite);
    jeu.ecarter(carte, quantite);
}

void Joueur::addNbAchatPhase(int nbAchatPossible) {
    m_nbAchatPossible += nbAchatPossible;
    std::cout<<DIM_TEXT<<GREEN<<"Vous avez "<<m_nbAchatPossible<<" achat(s) possible(s)."<<RESET<<std::endl;
}

void Joueur::addNbActionPhase(int nbActionPossible) {
    m_nbActionPossible += nbActionPossible;
}

void Joueur::ajouterRetirerValeurSupp(int nbValeurSup) {
    m_valeurSupp += nbValeurSup;
}

int Joueur::nbValeurDisponible() const {
    int val = m_valeurSupp;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        val += entry.second * (entry.first -> getValeur());
    }
    return val;
}

void Joueur::prendreArgent(int valeur) {

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
            int quantite = 0;
            for(int i = 0; i<entry.second; i++) {
                if(valeur>0) {
                    quantite++;
                    valeur -= entry.first -> getValeur();
                }
            }
            valeur -= (entry.first -> getValeur()) * quantite;
            cartes.push_back(std::make_pair(entry.first, quantite));
        }
    }
    for (auto entry : cartes ){
        Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, entry.first, - entry.second);
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
}

void Joueur::defausserCarte(Carte *carte) {
    Carte::ajoutSuppCarte(m_main, carte, -1);
    Carte::ajoutSuppCarte(m_defausse, carte, 1);
}

void Joueur::mettreEncoursDutilisationCartes(Carte* carte, int quantite) {
    Carte::ajoutSuppCarte(m_main, carte, -quantite);
    return Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte, quantite);
}



void Joueur::mainVersUtilise(Carte* carte){
    Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte, 1);
    Carte::ajoutSuppCarte(m_main, carte, -1);
}

void Joueur::mettreMainDansDefausse() {
    for(auto entry : m_main){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_main.clear();
}

void Joueur::mettreDefausseDansDeck() {
    for(auto entry : m_defausse){
        Carte::ajoutSuppCarte(m_deck, entry.first, entry.second);
    }
    m_defausse.clear();
}

bool Joueur::isInGodMode() {
    return m_godMode;
}

void Joueur::mettreUtiliseDansDefausse() {
    for(auto entry : m_carteEnCoursDutilisation){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_carteEnCoursDutilisation.clear();
}

void Joueur::mainVersDeck(Carte* carte, int quantite){
    Carte::ajoutSuppCarte(m_deck, carte, quantite);
    Carte::ajoutSuppCarte(m_main, carte, -quantite);
}








///////////////////////////////////////TOUR D UN JOUEUR + IHM
void Joueur::tourJoueur(Jeu& jeu){
    std::cout<<BLINK_ON<<BOLD_ON<<couleurJ<<"\n\n=============================================\n";
    std::cout<<"=============== TOUR JOUEUR "<<m_numJoueur<<" ===============\n";
    std::cout<<"=============================================\n\n"<<RESET<<std::endl;
    if(m_godMode) {
        m_nbAchatPossible = 100;
        m_nbActionPossible = 100;
        m_valeurSupp = 1000;
    } else {
        m_nbAchatPossible = 1;
        m_nbActionPossible = 1;
        m_valeurSupp = 0;
    }
    while(1){
        m_phaseActuelle->jouerPhase(jeu, *this);
        if(m_phaseActuelle->dernierePhase()) {
            jeu.commandePartieEstFinie();
            break;
        }
        m_phaseActuelle = &m_phaseActuelle->getPhaseSuivante();
    }
    m_phaseActuelle = &PhaseAction::getInstance();
}

void Joueur::commandeHELP(){
    std::cout<<GREEN<<INVERSE_ON<<"LIST DES COMMANDES :" <<RESET<<std::endl;
    std::cout<<DIM_TEXT<<UNDERLINE_ON<<GREEN<<"ATTENTION :"<<RESET<<DIM_TEXT<<GREEN;
    std::cout<<" les commandes sont disponibles en fonction de la phase ou de la carte joueur"<<RESET<<std::endl;
    std::cout<<GREEN<<std::endl;
    std::cout<<"\tFIN\tpour sortir d'une phase ou d'une commande" <<std::endl;
    std::cout<<"\tSHOWME\tpour montrer les cartes en main" <<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tACHAT\tpour acheter" <<std::endl;
    std::cout<<"\tACTION\tpour jouer les cartes Actions" <<std::endl;

    std::cout<<"\tUTILISER\tpour placer les cartes dans la main en cours d'utilisation pour pouvoir les utiliser" <<std::endl;
    std::cout<<"\tDFC\tpour defausser des cartes" <<std::endl;
    std::cout<<"\t" <<std::endl;
    std::cout<<"\t" <<std::endl;
    std::cout<<"\t" <<std::endl;
    std::cout<<"\t" <<std::endl;
    std::cout<<RED<<"\tGODMODE\t\tpour avoir tous les types de cartes" <<std::endl;
    std::cout<<RED<<"\tARRETJEU\tpour sortir du jeu" <<std::endl;
    std::cout<<RESET<<std::endl;
}

void Joueur::jouerRenovation(int quantite) {
    std::string commande;
    while(quantite > 0) {
        jeu.afficherReserve();
        afficherUtilise();
        std::cout << "Choisissez une carte à écarter.\n";
        afficherMain(true);
        int idCarte = 0;
        Carte* carte = nullptr;
        while(carte == nullptr) {
            carte = demandeChercherCarte(m_main, commande, idCarte);
            if(carte == nullptr){
                if(caseInsensitiveCompare(commande, "GODMODE")) {
                    continue;
                }
                return;
            }
        }
        ecarter(jeu, carte);
        commandeRecevoirCartePlateau(carte->getCout() + 2);
        quantite--;
    }

}

Carte* Joueur::demandeChercherCarte(std::vector<std::pair<Carte *, int>> li, std::string &commande, int& idCarte) {
    Carte* c = nullptr;
    std::cout << "ECRIRE NOM CARTE OU ID\n";
    while(1) {
        std::cin >> commande;
        if(caseInsensitiveCompare(commande, "FIN")){
            return c;
        } else if(caseInsensitiveCompare(commande, "GODMODE")){
            jeu.commandeGODMODE(m_main);
            m_nbAchatPossible = 100;
            m_nbActionPossible = 100;
            m_valeurSupp = 100;
            m_godMode = true;
            std::cout<<DIM_TEXT<<GREEN<<"Mode débogage activé."<<RESET<<std::endl;
            return c;
        }
        c = Carte::chercherCarte(li, commande, idCarte);
        if(c == nullptr){
            std::cout<<DIM_TEXT<<RED<<"carte : "<<commande<<" NON TROUVEE"<<RESET<<std::endl;
        } else {
            break;
        }
    }
    return c;
}

void Joueur::defaussPiocher(){
    
    std::string commande;
    while(m_deck.size()) {
        jeu.afficherReserve();
        afficherUtilise();
        std::cout << "Choisissez une carte à défausser.\n";
        afficherMain(true, [](Carte*) { return true; });
        int idCarte = 0;
        Carte* carte = nullptr;
        while(carte == nullptr) {
            carte = demandeChercherCarte(jeu.getReserve(), commande, idCarte);
            if(carte == nullptr){
                if(caseInsensitiveCompare(commande, "GODMODE")) {
                    continue;
                }
                return;
            }
        }
        defausserCarte(carte);
        piocher(1);
    }
}

void Joueur::reserveVersDefausse(Carte* carte, int quantite) {
    Carte::ajoutSuppCarte(m_defausse, carte, quantite);
    jeu.retirerDeReserve(carte, quantite);
}

void Joueur::commandeRecevoirCartePlateau(int coutMax, bool versDefausse) {
    std::string commande;
    
    jeu.afficherReserve(true, [coutMax](Carte* carte) -> bool {
        return carte->getCout() <= coutMax;
    });
    afficherUtilise();
    std::cout << "Choisissez une carte coutant jusqu'à " << coutMax << "\n";
    afficherMain();
    int idCarte = 0;
    Carte* carte = nullptr;
    while(carte == nullptr) {
        carte = demandeChercherCarte(jeu.getReserve(), commande, idCarte);
        if(carte == nullptr){
            if(caseInsensitiveCompare(commande, "GODMODE")) {
                continue;
            }
            return;
        }
    }
    if(carte->getCout() > coutMax) {
        std::cout << "Vous n'avez pas assez de valeur pour acheter cette carte.\n";
    }
    if(versDefausse) {
        reserveVersDefausse(carte);
    } else {
        reserveVersMain(carte);
    }
}

void Joueur::augmenterTresor(Jeu& jeu, int coutSup){
    std::string commande;
    jeu.afficherReserve();
    afficherUtilise();
    std::cout << "Choisissez une carte Trésor à écarter.\n";
    afficherMain(true, [](Carte* carte) { return carte->getTypeCarte() == TypeTresor; });
    int idCarte = 0;
    Carte* carte = nullptr;
    while(carte == nullptr) {
        carte = demandeChercherCarte(m_main, commande, idCarte);
        if(carte == nullptr){
            if(caseInsensitiveCompare(commande, "GODMODE")) {
                continue;
            }
            return;
        }
    }
    ecarter(jeu, carte);
    int coutMax = carte->getValeur() + coutSup;
    jeu.afficherReserve(true, [coutMax](Carte* carte) -> bool {
        return carte->getTypeCarte() == TypeTresor && carte->getCout() <= coutMax;
    });
    afficherUtilise();
    std::cout << "Choisissez une carte Trésor coutant jusqu'à " << coutMax << "\n";
    afficherMain();
    idCarte = 0;
    carte = nullptr;
    while(carte == nullptr) {
        carte = demandeChercherCarte(jeu.getReserve(), commande, idCarte);
        if(carte == nullptr){
            if(caseInsensitiveCompare(commande, "GODMODE")) {
                continue;
            }
            return;
        }
    }
    if(carte->getCout() > coutMax) {
        std::cout << "Vous n'avez pas assez de valeur pour acheter cette carte.\n";
    }
    reserveVersDefausse(carte);
}

void Joueur::afficherMain(bool pourPrendre, std::function<bool(Carte*)> condition, int start) {
    std::cout<<BOLD_ON<<couleurJ<< "---------------------------- Main -------------------------------\n"<<RESET;
    Carte::afficher(m_main, pourPrendre, condition, start);
    std::cout<<BOLD_ON<<couleurJ<< "-----------------------------------------------------------------\n"<<RESET;
}

void Joueur::afficherUtilise() {
    std::cout<<BOLD_ON<<couleurJ<< "----------------- Cartes en cours d'utilisation -----------------\n"<<RESET;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        std::cout<<entry.second << " ";
        Carte::afficherCarteEtDesc(entry.first);
    }
    std::cout<<BOLD_ON<<couleurJ<< "-----------------------------------------------------------------\n"<<RESET;
}

void Joueur::demandeEcarter(int quantite){
    std::string commande;
    for(int i = 0; i<quantite; i++) {
        jeu.afficherReserve();
        afficherUtilise();
        std::cout << "Choisissez une carte à écarter.\n";
        afficherMain(true, [](Carte*) { return true; });
        int idCarte = 0;
        Carte* carte = nullptr;
        while(carte == nullptr) {
            carte = demandeChercherCarte(m_main, commande, idCarte);
            if(carte == nullptr){
                if(caseInsensitiveCompare(commande, "GODMODE")) {
                    continue;
                }
                return;
            }
        }
        ecarter(jeu, carte);
    }
}

void Joueur::piocher(int quantite) {
    int nbCartes = 0;
    for (const auto& paire : m_deck) {
        nbCartes += paire.second;
    }
    for(int i = 0; i<quantite; i++){
        if(nbCartes == 0){
            mettreDefausseDansDeck();
            for (const auto& paire : m_deck) {
                nbCartes += paire.second;
            }
        }
        if(nbCartes == 0){
            if(!m_godMode) {
                std::cout<<DIM_TEXT<<RED<<"DECK VIDE"<<RESET<<std::endl;
            }
            break;
        }
        std::srand(std::time(0));
        // Generate a random number between 1 and nbCartes
        int choixAleatoire = std::rand() % nbCartes;

        //recherche de la carte
        for (auto& entry : m_deck) {
            choixAleatoire -= entry.second;
            if (choixAleatoire <= 0) { // carte trouvee donc on rajoute à la main
                Carte::ajoutSuppCarte(m_deck,entry.first, -1);
                Carte::ajoutSuppCarte(m_main,entry.first, 1);
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<< entry.first -> getNom()<<" pioché"<<RESET<<std::endl;
                nbCartes -= 1;
                break;
            }
        }
    }
}