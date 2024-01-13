#include "Jeu.h"
#include <iostream>

#include "Cuivre.h"
#include "Argent.h"
#include "Or.h"

#include "Domaine.h"
#include "Duche.h"
#include "Province.h"
#include "Malediction.h"

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

#include "PhaseAjustement.h"


//pour IHM
#include "CouleurTerminal.h"

Jeu::Jeu(int nbJoueur) : m_nbJoueur(nbJoueur), m_fini(false){
    for(int i = 0; i < nbJoueur; i++){
        m_joueurs.push_back(Joueur(i));
        initJoueur(m_joueurs.at(i));
    }
    initCartesPlateau();
    m_phaseActuelle = Phase::getPhaseCourante();

}

Jeu::~Jeu() {

    m_joueurs.clear();

    //delete phaseActuelle;//pose pb
    /*
    for (auto& it : m_cartesPlateau) {
        delete it.first;
    }*/
    m_cartesPlateau.clear();
    rebus.clear();

}

int Jeu::getNbJoueur(){
    return m_nbJoueur;
}

const std::string* Jeu::getNomPhaseActu() const {
    return m_phaseActuelle -> getNomPhase();
}

Joueur* Jeu::getJoueur(int i) {
    return &m_joueurs.at(i);
}

std::list<Carte*> Jeu::getToutesLesCartes() const {
    return toutesLesCartes;
}

const std::map<Carte*, int> Jeu::getCartesPlateau() const {
    return m_cartesPlateau;
}

bool Jeu::partieEstFinie() {
    auto it = m_cartesPlateau.find(Province::makeProvince());
    if(it == m_cartesPlateau.end() || it -> second == 0){
        return true;
    }
    int nbPilesVides = 0;
    for(Carte* c : toutesLesCartes){
        auto it = m_cartesPlateau.find(c);
        if(it == m_cartesPlateau.end() || it -> second == 0){
            nbPilesVides++;
        }
        if(nbPilesVides == 3){
            return true;
        }
    }
    return false;
}

int Jeu::getGagnant() {
    int pointMax = 0;
    int gagnant = 0;
    for(int joueurNum = 0; joueurNum < m_nbJoueur; joueurNum++){
        int point = m_joueurs.at(joueurNum).getVictoireDansDeck();
        if(point > pointMax){
            gagnant = joueurNum;
            pointMax = point;
        }
    }
    return gagnant;
}

bool Jeu::getFini() const {return m_fini;}

void Jeu::setFini(bool fini){
    m_fini = fini;
}

void Jeu::afficherCartesPlateau() {
    for (const auto& entry : m_cartesPlateau) {
        std::cout<< "   " << *(entry.first) << ": " << entry.second << "\n";
    }
}

bool Jeu::carteDisponible(Carte *carte) {
    return m_cartesPlateau.find(carte) -> second > 0;
}
bool Jeu::retirerCarteDisponible(Carte *carte, int quantite) {
    if(carteDisponible(carte)){
        Carte::ajoutSuppCarte(m_cartesPlateau, carte,-quantite);
        return true;
    }

    return false;
}

void Jeu::ajoutCartesDefausses(Carte &carte, int quantite) {
    for(Joueur& j : m_joueurs){
        j.prendreCartePlateau(&carte, *this, quantite, false);
    }
}

void Jeu::mettreDansRebus(Carte *carte) {
    rebus.push_back(carte);
}


///Methode initialisation en debut de partie
void Jeu::initCartesPlateau() {

    /////////////// CARTE VICTOIRE
    int quantite = 8;
    if(m_nbJoueur != 2){
        quantite = 12;
    }
    Carte::ajoutSuppCarte(m_cartesPlateau, Domaine::makeDomaine(),quantite);
    Carte::ajoutSuppCarte(m_cartesPlateau, Duche::makeDuche(),quantite);
    Carte::ajoutSuppCarte(m_cartesPlateau, Province::makeProvince(),quantite);

    /////////////// CARTE TRESOR
    Carte::ajoutSuppCarte(m_cartesPlateau, Malediction::makeMalediction(),30);
    Carte::ajoutSuppCarte(m_cartesPlateau, Cuivre::makeCuivre(),60);
    Carte::ajoutSuppCarte(m_cartesPlateau, Argent::makeArgent(),40);
    Carte::ajoutSuppCarte(m_cartesPlateau, Or::makeOr(),30);

    /////////////// CARTE ROYAUME
    Carte::ajoutSuppCarte(m_cartesPlateau, Atelier::makeAtelier(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Bucheron::makeBucheron(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Cave::makeCave(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Chapelle::makeChapelle(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Forgeron::makeForgeron(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Marche::makeMarche(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Mine::makeMine(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Renovation::makeRenovation(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Sorciere::makeSorciere(),10);
    Carte::ajoutSuppCarte(m_cartesPlateau, Village::makeVillage(),10);

    //Pour avoir une liste constante de pointeurs pour toutes les cartes
    for(std::pair<Carte*, int> p : m_cartesPlateau){
        toutesLesCartes.push_back(p.first);
    }

}
void Jeu::initJoueur(Joueur& joueur){
    joueur.prendreCartePlateau(Cuivre::makeCuivre(), *this, 7, true);
    joueur.prendreCartePlateau(Domaine::makeDomaine(), *this, 3, true);

    joueur.piocherCarteDeck(5);
}
void Jeu::tour(int numJoueur){
    while(1){
        for(int i = numJoueur; i < m_nbJoueur; i++){
            m_joueurs.at(i).tourJoueur(*this);
            if(m_fini){
                std::cout<<"SORTI DU JEU\n";
                break;
            }
        }
        if(m_fini){
            std::cout<<"SORTI DU JEU\n";
            break;
        }
    }

}

void Jeu::changementDePhase(){
    m_phaseActuelle -> phaseSuivante();
    m_phaseActuelle = Phase::getPhaseCourante();
}
bool Jeu::estAPhaseAjustement(){
    return m_phaseActuelle == PhaseAjustement::getInstancePhaseAjustement();
}
void Jeu::initJoueurPhase(Joueur& joueur) {
    m_phaseActuelle -> initJoueur(joueur);
}

/////////////////////////////////////// TOUR + IHM
void Jeu::lancementJeu() {
    std::cout<<BLINK_ON<<BOLD_ON<<"\n\n==============================================\n";
    std::cout<<"=============== LANCEMENT JEU  ===============\n";
    std::cout<<"==============================================\n\n"<<RESET<<std::endl;
    //distribution



    // TODO : faire l'enregistrement la si on a le temp
    afficherCartesPlateau();
    tour(0);//pour l'instant pas d'enregistrement donc le jeu commence au joueur 0

    //TODO : faire en registrement pour partie non gangé

    std::cout<<BLINK_ON<<BOLD_ON<<"\n\n==============================================\n";
    std::cout<<"=============== SORTIR DU JEU  ===============\n";
    std::cout<<"==============================================\n\n"<<RESET<<std::endl;

}

bool Jeu::commandePartieEstFinie() {
    if(partieEstFinie()) {
        int m_numJoueur = getGagnant();
        std::cout<<BOLD_ON<<INVERSE_ON<<INVERSE_ON;
        std::cout<<"JOUEUR "<<m_numJoueur<<" A GAGNER"<<RESET<<"\n";
        setFini(true);
    }
    return false;
}