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

std::list<Carte*> Jeu::getToutesLesCartes() const {
    return allInstancesCards;
}

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
    for(int joueurNum = 0; joueurNum < m_nbJoueur; joueurNum++){
        int point = m_joueurs.at(joueurNum).getVictoireDansDeck();
        if(point > pointMax){
            gagnant = joueurNum;
            pointMax = point;
        }
    }
    return gagnant;
}

bool Jeu::estFini() const {return m_fini;}

void Jeu::setFini(bool fini){
    m_fini = fini;
}

// bool Jeu::carteDisponible(Carte *carte) {
//     return m_cartesPlateau.find(carte) -> second > 0;
// }
// bool Jeu::retirerCarteDisponible(Carte *carte, int quantite) {
//     if(carteDisponible(carte)){
//         Carte::ajoutSuppCarte(m_cartesPlateau, carte,-quantite);
//         return true;
//     }

//     return false;
// }

void Jeu::ajoutCartesDefausses(Carte* carte, int quantite) {
    for(Joueur& j : m_joueurs){
        j.prendreCartePlateau(*this, carte, quantite, true);
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

    Carte::ajoutSuppCarte(reserve, Domaine::makeDomaine(),quantite);
    Carte::ajoutSuppCarte(reserve, Duche::makeDuche(),quantite);
    Carte::ajoutSuppCarte(reserve, Province::makeProvince(),quantite);

    /////////////// CARTE TRESOR
    Carte::ajoutSuppCarte(reserve, Malediction::makeMalediction(),30);
    Carte::ajoutSuppCarte(reserve, Cuivre::makeCuivre(),60);
    Carte::ajoutSuppCarte(reserve, Argent::makeArgent(),40);
    Carte::ajoutSuppCarte(reserve, Or::makeOr(),30);

    /////////////// CARTE ROYAUME
    Carte::ajoutSuppCarte(reserve, Atelier::makeAtelier(),10);
    Carte::ajoutSuppCarte(reserve, Bucheron::makeBucheron(),10);
    Carte::ajoutSuppCarte(reserve, Cave::makeCave(),10);
    Carte::ajoutSuppCarte(reserve, Chapelle::makeChapelle(),10);
    Carte::ajoutSuppCarte(reserve, Forgeron::makeForgeron(),10);
    Carte::ajoutSuppCarte(reserve, Marche::makeMarche(),10);
    Carte::ajoutSuppCarte(reserve, Mine::makeMine(),10);
    Carte::ajoutSuppCarte(reserve, Renovation::makeRenovation(),10);
    Carte::ajoutSuppCarte(reserve, Sorciere::makeSorciere(),10);
    Carte::ajoutSuppCarte(reserve, Village::makeVillage(),10);

    //Pour avoir une liste constante de pointeurs pour toutes les cartes
    for(std::pair<Carte*, int> p : reserve){
        allInstancesCards.push_back(p.first);
    }

}
void Jeu::initJoueur(Joueur& joueur){
    joueur.prendreCartePlateau(*this, Cuivre::makeCuivre(), 7, true);
    joueur.prendreCartePlateau(*this, Domaine::makeDomaine(), 3, true);

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
    afficherCartesPlateau();
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

void Jeu::afficherCartesPlateau() {
    std::cout<<"CARTE SUR LE PLATEAU : \n";
    for (const auto& entry : reserve) {
        std::cout<< "   " << *(entry.first) << ": " << entry.second << "\n";
    }
}

Carte* Jeu::demandeCartePlateau(Joueur& joueur, std::string& commande) {
    return joueur.demandeChercherCarte(reserve, commande);
}