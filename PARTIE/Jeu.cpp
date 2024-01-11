#include "Jeu.h"
#include <iostream>

#include "Cuivre.h"
#include "Argent.h"
#include "Or.h"

#include "Domaine.h"
#include "Duche.h"
#include "Province.h"
#include "Malediction.h"

#include "Marche.h"
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

}

void Jeu::nop(){}

int Jeu::getNbJoueur(){
    return m_nbJoueur;
}
const std::string* Jeu::getNomPhaseActu() const {
    return m_phaseActuelle -> getNomPhase();
}
Joueur* Jeu::getJoueur(int i) {
    return &m_joueurs.at(i);
}
const std::map<Carte*, int> Jeu::getCartesPlateau() const {
    return m_cartesPlateau;
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


///Methode initialisation en debut de partie
void Jeu::initCartesPlateau() {

    /////////////// CARTE VICTOIRE
    if(m_nbJoueur == 2){
        Carte::ajoutSuppCarte(m_cartesPlateau, Domaine::makeDomaine(),8);
        Carte::ajoutSuppCarte(m_cartesPlateau, Duche::makeDuche(),8);
        Carte::ajoutSuppCarte(m_cartesPlateau, Province::makeProvince(),8);
    }
    else if(m_nbJoueur == 3 || m_nbJoueur == 4){
        Carte::ajoutSuppCarte(m_cartesPlateau, Domaine::makeDomaine(),12);
        Carte::ajoutSuppCarte(m_cartesPlateau, Duche::makeDuche(),12);
        Carte::ajoutSuppCarte(m_cartesPlateau, Province::makeProvince(),12);
    }

    /////////////// CARTE TRESOR
    Carte::ajoutSuppCarte(m_cartesPlateau, Malediction::makeMalediction(),30);
    Carte::ajoutSuppCarte(m_cartesPlateau, Cuivre::makeCuivre(),60);
    Carte::ajoutSuppCarte(m_cartesPlateau, Argent::makeArgent(),40);
    Carte::ajoutSuppCarte(m_cartesPlateau, Or::makeOr(),30);

    /////////////// CARTE ROYAUME

    Carte::ajoutSuppCarte(m_cartesPlateau, Marche::makeMarche(),10);

}
void Jeu::initJoueur(Joueur& joueur){
    joueur.prendreCartePlateau(Cuivre::makeCuivre(), *this, 7, true);
    joueur.prendreCartePlateau(Domaine::makeDomaine(), *this, 3, true);
}
void Jeu::tour(int numJoueur){
    for(int i = numJoueur; i < m_nbJoueur; i++){
        m_joueurs.at(i).tourJoueur(*this);
        if(m_fini){
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

    // TODO : faire l'enregistrement la si on a le temp
    afficherCartesPlateau();
    tour(0);//pour l'instant pas d'enregistrement donc le jeu commence au joueur 0

    //TODO : faire en registrement pour partie non gangé

    std::cout<<BLINK_ON<<BOLD_ON<<"\n\n==============================================\n";
    std::cout<<"=============== SORTIR DU JEU  ===============\n";
    std::cout<<"==============================================\n\n"<<RESET<<std::endl;

}