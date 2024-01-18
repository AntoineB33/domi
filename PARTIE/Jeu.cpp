#include "Jeu.h"
#include <iostream>
#include <functional>

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
#include "PhaseAction.h"
#include "PhaseAchat.h"


//pour IHM
#include "CouleurTerminal.h"

Jeu::Jeu(int nbJoueur) : m_nbJoueur(nbJoueur), m_fini(false){
    for(int i = 0; i < nbJoueur; i++){
        m_joueurs.push_back(Joueur(i));
        initJoueur(m_joueurs.at(i));
    }
    initCartesPlateau();
}

Jeu::~Jeu() {
}

int Jeu::getNbJoueur(){
    return m_nbJoueur;
}

Joueur* Jeu::getJoueur(int i) {
    return &m_joueurs.at(i);
}

// std::list<Carte*> Jeu::getToutesLesCartes() const {
//     return allInstancesCards;
// }

bool Jeu::partieEstFinie() {
    int nbPilesVides = 0;
    for(long unsigned int i = 0; i<reserve.size(); i++){
        if(reserve.at(i).first->getNom() == "Province" && reserve.at(i).second == 0){
            return true;
        } else if (reserve.at(i).second == 0){
            nbPilesVides++;
            if(nbPilesVides == 3){
                return true;
            }
        }
    }
    return false;
}

int Jeu::getGagnant() {
    int pointMax = 0;
    int gagnant = 0;
    for(Joueur& j : m_joueurs){
        int point = j.getVictoireDansDeck();
        if(point > pointMax){
            gagnant = j.getId();
            pointMax = point;
        }
    }
    return gagnant;
}

bool Jeu::hasCarteAchetable(int disponible) {
    for(long unsigned int i = 0; i<reserve.size(); i++){
        if(reserve.at(i).first->getCout() <= disponible && reserve.at(i).second > 0){
            return true;
        }
    }
    return false;
}

bool Jeu::estFini() const {return m_fini;}

void Jeu::setFini(bool fini){
    m_fini = fini;
}

// bool Jeu::carteDisponible(Carte *carte) {
//     return m_cartesPlateau.find(carte) -> second > 0;
// }
void Jeu::retirerDeReserve(Carte *carte) {
    Carte::ajoutSuppCarte(reserve, carte, -1);
}

void Jeu::ajoutCartesDefausses(Carte* carte, int quantite) {
    for(Joueur& j : m_joueurs){
        j.reserveVersDeck(*this, carte, quantite, true);
    }
}

void Jeu::ecarter(Carte *carte, int quantite) {
    for(int i = 0; i < quantite; i++) {
        rebus.push_back(carte);
    }
}


///Methode initialisation en debut de partie
void Jeu::initCartesPlateau() {

    /////////////// CARTE VICTOIRE
    int quantite = 8;
    if(m_nbJoueur != 2){
        quantite = 12;
    }
    reserve = {
            {Domaine::makeDomaine(), quantite},
            {Duche::makeDuche(), quantite},
            {Province::makeProvince(), quantite},
            {Malediction::makeMalediction(), 30},
            {Cuivre::makeCuivre(), 60},
            {Argent::makeArgent(), 40},
            {Or::makeOr(), 30},
            {Atelier::makeAtelier(), 10},
            {Bucheron::makeBucheron(), 10},
            {Cave::makeCave(), 10},
            {Chapelle::makeChapelle(), 10},
            {Forgeron::makeForgeron(), 10},
            {Marche::makeMarche(), 10},
            {Mine::makeMine(), 10},
            {Renovation::makeRenovation(), 10},
            {Sorciere::makeSorciere(), 10},
            {Village::makeVillage(), 10}

    };

    // Carte::ajoutSuppCarte(reserve, Domaine::makeDomaine(),quantite);
    // Carte::ajoutSuppCarte(reserve, Duche::makeDuche(),quantite);
    // Carte::ajoutSuppCarte(reserve, Province::makeProvince(),quantite);

    // /////////////// CARTE TRESOR
    // Carte::ajoutSuppCarte(reserve, Malediction::makeMalediction(),30);
    // Carte::ajoutSuppCarte(reserve, Cuivre::makeCuivre(),60);
    // Carte::ajoutSuppCarte(reserve, Argent::makeArgent(),40);
    // Carte::ajoutSuppCarte(reserve, Or::makeOr(),30);

    // /////////////// CARTE ROYAUME
    // Carte::ajoutSuppCarte(reserve, Atelier::makeAtelier(),10);
    // Carte::ajoutSuppCarte(reserve, Bucheron::makeBucheron(),10);
    // Carte::ajoutSuppCarte(reserve, Cave::makeCave(),10);
    // Carte::ajoutSuppCarte(reserve, Chapelle::makeChapelle(),10);
    // Carte::ajoutSuppCarte(reserve, Forgeron::makeForgeron(),10);
    // Carte::ajoutSuppCarte(reserve, Marche::makeMarche(),10);
    // Carte::ajoutSuppCarte(reserve, Mine::makeMine(),10);
    // Carte::ajoutSuppCarte(reserve, Renovation::makeRenovation(),10);
    // Carte::ajoutSuppCarte(reserve, Sorciere::makeSorciere(),10);
    // Carte::ajoutSuppCarte(reserve, Village::makeVillage(),10);

    //Pour avoir une liste constante de pointeurs pour toutes les cartes
    // for(std::pair<Carte*, int> p : reserve){
    //     allInstancesCards.push_back(p.first);
    // }

}
void Jeu::initJoueur(Joueur& joueur){
    for(int i = 0; i<7; i++){
        joueur.reserveVersDeck(*this, Cuivre::makeCuivre(), true);
    }
    for(int i = 0; i<3; i++){
        joueur.reserveVersDeck(*this, Domaine::makeDomaine(), true);
    }
    joueur.piocherCarteDeck(5);
}

void Jeu::commandeGODMODE(std::vector<std::pair<Carte*, int>>& m) {
    for(std::pair<Carte*, int> p : reserve){
        Carte::ajoutSuppCarte(m, p.first, 10);
    }
}

// void Jeu::initJoueurPhase(Joueur& joueur) {
//     m_phaseActuelle -> initJoueur(joueur);
// }

/////////////////////////////////////// TOUR + IHM
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

void Jeu::lancementJeu() {
    std::cout<<BLINK_ON<<BOLD_ON<<"\n\n==============================================\n";
    std::cout<<"=============== LANCEMENT JEU  ===============\n";
    std::cout<<"==============================================\n\n"<<RESET<<std::endl;
    //distribution



    // TODO : faire l'enregistrement la si on a le temp
    afficherReserve();
    //si nouvelle partie, on remet s'assure d etre dans la bonne phase

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

int Jeu::afficherReserve(bool pourPrendre, std::function<bool(Carte*)> condition) {
    std::cout<<"CARTE SUR LE PLATEAU : \n";
    return Carte::afficher(reserve, pourPrendre, condition);
}

// Carte* Jeu::demandeCartePlateau(Joueur& joueur, std::string& commande) {
//     return joueur.demandeChercherCarte(reserve, commande);
// }