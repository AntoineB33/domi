#include "Joueur.h"
#include "Jeu.h"
#include "Carte.h"
#include "Phase.h"
#include "PhaseAction.h"

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

// std::ostream& operator<<(std::ostream& os, const Joueur& joueur) {
//     os << "====================> Joueur " << joueur.m_numJoueur << ":\n";
//     os << "nb achat restant : " << joueur.m_nbAchatPossible << "\t";
//     os << "nb action restant : " << joueur.m_nbActionPossible << "\n";

//     os << "Main:\n";
//     for (const auto& entry : joueur.m_main) {
//         os << "   " << *(entry.first) << ": " << entry.second << "\n";
//     }

//     os << "Cartes en cours d'utilisation:\n";
//     for (const auto& entry : joueur.m_carteEnCoursDutilisation) {
//         os << "   " << *(entry.first) << ": " << entry.second << "\n";
//     }

//     os << "Deck:\n";
//     for (const auto& entry : joueur.m_deck) {
//         os << "   " << *(entry.first) << ": " << entry.second << "\n";
//     }

//     os << "Défausse:\n";
//     for (const auto& carte : joueur.m_defausse) {
//         os << "   " << *carte << "\n";
//     }
//     return os;
// }

//GETTERS
const std::vector<std::pair<Carte*, int>>& Joueur::getMain() const {
    return m_main;
}

const std::vector<std::pair<Carte*, int>>& Joueur::getCarteEnCoursDutilisation() const {
    return m_carteEnCoursDutilisation;
}

// const std::list<Carte*>& Joueur::getDeck() const {
//     return m_deck;
// }

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




///////////////////////////////////////ACTION DU JOUEUR
// bool Joueur::acheterCarte(Jeu& jeu, Carte* carte){
//     if(prendreCartePlateau(jeu, carte)) {
//         m_nbAchatPossible -= 1;
//         return true;
//     }
//     return false;
// }

// bool Joueur::jouerCarteAction(Jeu& jeu, Carte* c){
//     auto it = m_carteEnCoursDutilisation.find(c);
//     if(it != m_carteEnCoursDutilisation.end()){
//         if( c -> getTypeCarte() == TypeRoyaume){
//             c -> jouerAction(*this, jeu);
//             //on retire la carte
//             if(Carte::ajoutSuppCarte(m_carteEnCoursDutilisation,c,-1)){
//                 Carte::ajoutSuppCarte(m_defausse,c,1);
//             }
//             m_nbActionPossible -= 1;
//             return true;
//         }
//     }
//     return false;
// }

// bool Joueur::ajuster(){
//     size_t q = 5;
//     //vider
//     defausserCarte();

//     //piocher
//     if(m_deck.size() < q){
//         piocherCarteDeck(m_deck.size());
//         q -= m_deck.size();
//         if(m_deck.size() < 5) {
//             mettreCarteDefausseDansDeck();
//         }
//         piocherCarteDeck(q);
//     }
//     else{
//         piocherCarteDeck(q);
//     }
//     return true;
// }

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
void Joueur::reserveVersMain(Jeu& jeu, Carte* carte) {
    jeu.retirerDeReserve(carte);
    Carte::ajoutSuppCarte(m_main ,carte , -1);
}

void Joueur::ecarter(Jeu& jeu, Carte* carte, int quantite){
    Carte::ajoutSuppCarte(m_main, carte, -quantite);
    jeu.ecarter(carte, quantite);
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


///////////////////////////////////////FONCTION PRIVATE

int Joueur::nbValeurDisponible() const {
    int val = m_valeurSupp;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        val += entry.second * (entry.first -> getValeur());
    }
    return val;
}

// bool Joueur::peutAcheterCarte(Carte* carte, Jeu& jeu){
//     // il faut que le carte soit encore disponible a l'achat
//     bool b = jeu.carteDisponible(carte);
//     if(!b){
//         return false;
//     }
//     // que le joueur est l'argent necessaire
//     b = b && nbValeurDisponible() >= carte -> getCout();
//     if(!b){
//         return false;
//     }
//     // que le joueur est au moins un point d'achat
//     b =b && m_nbAchatPossible > 0;
//     if(!b){
//         return false;
//     }
//     return   b;
// }

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

    // //cas specifique
    // if(disponible == valeur){
    //     for (auto entry : cartes ){
    //         Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, entry.first, - entry.second);
    //         Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    //     }
    //     return true;
    // }
    // std::sort(cartes.begin(), cartes.end(), [](const auto& a, const auto& b) {
    //     return a.first->getValeur() > b.first->getValeur();
    // });
    // // Parcours les cartes triees et retire la quantite necessaire pour atteindre la valeur voulue
    // for (const auto& carte : cartes) {
    //     int quantiteRetiree = std::min(carte.first->getValeur(), carte.second);
    //     valeur -= quantiteRetiree * carte.first->getValeur();
    //     m_carteEnCoursDutilisation[carte.first] -= quantiteRetiree;

    //     Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte.first, -1);
    //     Carte::ajoutSuppCarte(m_defausse, carte.first, 1);
    //     if (valeur == 0) {
    //         break;// on sort
    //     }
    // }
}

// std::list<Carte*> Joueur::piocherCarteDeck(int quantite){
//     std::list<Carte*> cartes;
//     //calcul nombre de carte dans le deck
//     int nbCartes = 0;
//     for (const auto& paire : m_deck) {
//         nbCartes += paire.second;
//     }
//     //pioche carte
//     while(quantite > 0 && nbCartes > 0){
//         //aleatoire
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> distrib(1, nbCartes);
//         int choixAleatoire = distrib(gen) ;

//         //recherche de la carte
//         for (auto& entry : m_deck) {
//             choixAleatoire -= entry.second;
//             if (choixAleatoire <= 0) { // carte trouvee donc on rajoute à la main
//                 Carte::ajoutSuppCarte(m_deck,entry.first, -1);
//                 Carte::ajoutSuppCarte(m_main,entry.first, 1);
//                 cartes.push_back(entry.first);
//                 quantite -= 1;
//                 nbCartes -= 1;
//                 break;
//             }
//         }
//     }
//     return cartes;
// }

void Joueur::defausserCarte(Carte *carte) {
    Carte::ajoutSuppCarte(m_main, carte, -1);
    Carte::ajoutSuppCarte(m_defausse, carte, 1);
}

// void Joueur::defausserCarte() {//defausser tout
//     for(auto entry : m_main){
//         Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
//     }
//     m_main.clear();
//     for(auto entry : m_carteEnCoursDutilisation){
//         Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
//     }
//     m_carteEnCoursDutilisation.clear();
//     return true;
// }

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








///////////////////////////////////////TOUR D UN JOUEUR + IHM
void Joueur::tourJoueur(Jeu& jeu){
    std::cout<<BLINK_ON<<BOLD_ON<<couleurJ<<"\n\n=============================================\n";
    std::cout<<"=============== TOUR JOUEUR "<<m_numJoueur<<" ===============\n";
    std::cout<<"=============================================\n\n"<<RESET<<std::endl;
    if(m_godMode) {
        m_nbAchatPossible = 100;
        m_nbActionPossible = 100;
    } else {
        m_nbAchatPossible = 1;
        m_nbActionPossible = 1;
    }
    m_valeurSupp = 0;
    while(!m_phaseActuelle->dernierePhase() && !jeu.commandePartieEstFinie()){
        m_phaseActuelle->jouerPhase(jeu, *this);
        m_phaseActuelle = &m_phaseActuelle->getPhaseSuivante();
    }
    m_phaseActuelle = &PhaseAction::getInstance();
}

// void Joueur::jouerPhase(Jeu& jeu){
//     std::string commande = " ";
//     while((jeu.estAPhaseAction() && m_nbActionPossible>0) || (jeu.estAPhaseAchat() && m_nbAchatPossible>0)){
//         std::cout<<BOLD_ON<<couleurJ<<"\n\n==> ECRIRE COMMANDE\n"<<RESET;
//         std::cout<<DIM_TEXT<<"possibilité d'écrire la commande : "<<UNDERLINE_ON<<"HELP\n"<<RESET;
//         std::cin>>commande;
//         if(commande == "HELP"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeHELP();
//         }
//         else if(commande == "FIN"){
//             break;
//         }
//         else if(commande == "SHOWME"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeSHOWME();
//         }
//         else if(commande =="ACHAT" && jeu.estAPhaseAchat()) {
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeAchat(jeu);
//         }
//         else if (commande == "ACTION" && jeu.estAPhaseAction()){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeAction(jeu);
//         }
//         else if(commande == "UTILISER"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeMettreCarteUtilisation();
//         }
//         else if(commande == "GODMODE"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeGODMODE(jeu);
//         }
//         else if(commande == "ARRETJEU"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             jeu.setFini(true);
//             std::cout<<BOLD_ON<<"=== ARRET DU JEU ===\n"<<RESET;
//             break;
//         }
//         else {
//             std::cout<<DIM_TEXT<<RED<<"commande "<<commande<<UNDERLINE_ON<<" non disponible \n"<<RESET;
//         }
//     }

// }

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

void Joueur::commandeSHOWME(){
    std::cout<<BOLD_ON<<couleurJ<<"NB ACHAT POSSIBLE : "<<m_nbAchatPossible;
    std::cout<<"\tNB ACTION POSSIBLE : "<<m_nbActionPossible<<"\n"<<RESET;

    std::cout<<BOLD_ON<<couleurJ<< "Main:\n"<<RESET<<couleurJ;
    for (const auto& entry : m_main) {
        std::cout << "   " << *(entry.first) << ": " << entry.second << "\n";
    }
    std::cout <<BOLD_ON<<couleurJ<< "Cartes en cours d'utilisation:\n"<<RESET<<couleurJ;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        std::cout << "   " << *(entry.first) << ": " << entry.second << "\n";
    }
    std::cout<<RESET<<std::endl;
}

Carte* Joueur::demandeChercherCarte(std::vector<std::pair<Carte *, int>> li, std::string &commande, int& idCarte) const {
    Carte* c = nullptr;
    std::cout << "ECRIRE NOM CARTE OU ID\n";
    while(1) {
        std::cin >> commande;
        if(caseInsensitiveCompare(commande, "FIN")){
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

// int Joueur::demandeQuantiteCarte(std::map<Carte*,int>& m, Carte* c ,std::string &commande){
//     auto it = m.find(c);
//     if(it== m.end()){
//         std::cout<<"ERREUR CARTE INEXISTANTE\n";
//         return 0;
//     }
//     int q = -1;
//     int nbMAX = it -> second;
//     while(1){
//         std::cout<<"QUANTITE VOULUE : "<<DIM_TEXT<<ITALIC_ON<<"(attention aux espaces)\n";
//         std::cout<<DIM_TEXT<<ITALIC_ON<<"(TOUT\tprend la quantité maximal disponible)\n"<<RESET;
//         std::cin>> commande;
//         //cas pécifique
//         if(commande == "TOUT"){
//             return nbMAX;
//         }
//         else if(commande =="FIN"){
//             return 0;
//         }

//         try {
//             q = std::stoi(commande);
//         }
//         catch (std::invalid_argument const &e) {
//             std::cout <<DIM_TEXT<<RED<< "ERROR : entree invalide" << RESET<<std::endl;
//         }
//         catch (std::out_of_range const &e) {
//             std::cout << DIM_TEXT<<RED<<"ERROR : nombre trop grand"<<RESET<< std::endl;
//         }

//         //verification : arret de la boucle ?
//         if(!(0<= q  && q <= nbMAX)){
//             std::cout << DIM_TEXT<<RED<<"ERROR : nombre non compris entre 0 et quantite disponible : "<< nbMAX <<RESET<< std::endl;
//         }
//         else{
//             return q;
//         }
//     }
//     return 0;
// }

// std::list<Carte*> Joueur::commandeEcarter(Jeu& jeu, int quantite) {
//     std::list<Carte*> li;
//     for(int i = 0; i< quantite; i++) {
//         std::cout<<DIM_TEXT<<"Seuls les cartes dans la main sont défaussables\n"<<RESET;
//         std::string commande = "";
//         Carte* c = nullptr;
//         commandeSHOWME();
//         while(1){
//             int idCarte = -1;
//             c = demandeChercherCarte(m_main, commande, idCarte);
//             if(c != nullptr){
//                 ecarter(jeu,c,1);
//                 std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" écarté"<<RESET<<std::endl;
//                 li.push_back(c);
//                 break;
//             }
//             if(commande == "FIN"){
//                 break;
//             }
//         }
//         if(commande == "FIN"){
//             break;
//         }
//     }
//     return li;
// }

void Joueur::defaussPiocher(){
    std::string commande = " ";
    while(1){
        std::cout<<std::endl;
        commandeSHOWME();
        std::cout<<DIM_TEXT<<"possibilité de défausser : "<<RESET;
        Carte* c = nullptr;
        while(c == nullptr) {
            int idCarte = -1;
            c = demandeChercherCarte(m_main, commande, idCarte);
        }
        if(commande == "FIN"){
            break;
        }
        defausserCarte(c);
        if(!commandePiocherCarteDeck(1)) {
            break; // si le deck est vide
        }
    }
}

void Joueur::augmenterTresor(Jeu& jeu, int quantite){
    (void)jeu;
    (void)quantite;
    // std::list<Carte*> li = commandeEcarter(jeu, 1);
    // if(li.empty()){
    //     return;
    // }
    // int coutMax = li.front() -> getCout() + quantite;
    // std::string commande = " ";
    // jeu.afficherReserve();
    // std::cout<<std::endl;
    // std::cout<<DIM_TEXT<<"Prenez une carte Trésor de la réserve : "<<RESET;
    // while(commande != "FIN") {
    //     Carte* c = jeu.demandeCartePlateau(*this, commande);
    //     if(c != nullptr && c -> getTypeCarte() == TypeTresor && c -> getCout() <= coutMax) {
    //         jeu.retirerCarteDisponible(c,1);
    //         Carte::ajoutSuppCarte(m_main, c, 1);
    //         break;
    //     } else {
    //         std::cout<<DIM_TEXT<<RED<<"carte : "<<commande<<" invalide."<<RESET<<std::endl;
    //     }
    // }
}

// void Joueur::commandeAchat(Jeu &jeu){
//     jeu.afficherReserve();
//     std::cout<<std::endl;
//     std::string commande = "";
//     Carte* c = nullptr;
//     while(commande != "FIN"){
//         if(m_nbAchatPossible <= 0){
//             std::cout<<DIM_TEXT<<RED<<"PAS ASSEZ DE POINT D ACHAT : fin d'achat\n"<<RESET;
//             break;
//         }
//         c = jeu.demandeCartePlateau(*this, commande);
//         if(c != nullptr){
//             if(acheterCarte(c,jeu)){
//                 std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" achetee "<<RESET<<std::endl;
//             }
//             else{
//                 std::cout<<DIM_TEXT<<RED<<"impossible d'acheter carte : "<<commande<<RESET<<std::endl;
//             }
//         }
//     }
// }

// void Joueur::commandeAction(Jeu &jeu){
//     std::cout<<"CARTE EN COURS D UTILISATION : \n";
//     Carte::afficher(m_carteEnCoursDutilisation);
//     std::cout<<std::endl;
//     std::string commande = "";
//     Carte* c = nullptr;
//     while(commande != "FIN"){
//         if(m_nbActionPossible <= 0){
//             std::cout<<DIM_TEXT<<RED<<"PAS ASSEZ DE POINT D ACTION : fin d'action\n"<<RESET;
//             break;
//         }
//         c = demandeChercherCarte(m_carteEnCoursDutilisation, commande);
//         if(c != nullptr){
//             if(jouerCarteAction(c, jeu)){
//                 std::cout<<DIM_TEXT<<GREEN<<"carte jouer\n"<<RESET;
//             }
//             else{
//                 std::cout<<DIM_TEXT<<RED<<"ne pas faire l'action\n";
//                 std::cout<<ITALIC_ON<<"(ce n'est peut etre pas une carte Action ou est dans les cartes en cours d utilisation)\n"<<RESET;
//             }

//         }
//     }
// }

// void Joueur::commandeMettreCarteUtilisation() {
//     std::string commande = "";
//     Carte* c = nullptr;
//     int q;
//     commandeSHOWME();
//     while(commande != "FIN"){
//         c = demandeChercherCarte(m_main, commande);
//         if(c != nullptr){
//             q = demandeQuantiteCarte(m_main, c, commande);
//             if(mettreEncoursDutilisationCartes(c,q)){
//                 std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" mise en cours d'utilisation"<<RESET<<std::endl;
//             }
//         }
//     }
// }

void Joueur::commandeGODMODE(Jeu& jeu){
    jeu.commandeGODMODE(m_main);
    m_nbAchatPossible = 100;
    m_nbActionPossible = 100;
    m_godMode = true;
    std::cout<<BOLD_ON<<DIM_TEXT<<"=== GOD MODE ===\n"<<RESET;
}

// void Joueur::faireAjustement(Jeu& jeu) {
//     std::string commande = " ";
//     while(commande != "FIN"){
//         std::cout<<BOLD_ON<<couleurJ<<"\n==> ECRIRE COMMANDE\n"<<RESET;
//         std::cout<<DIM_TEXT<<"possibilité d'écrire la commande : HELP\n"<<RESET;
//         std::cout<<DIM_TEXT<<"en phase ajustement, la commande : FIN, défausse automatiquement toutes les cartes et pioche les cartes\n"<<RESET;
//         std::cin>> commande;
//         if(commande == "HELP"){
//             commandeHELP();
//         }
//         else if(commande == "FIN"){
//             ajuster();
//             commandeSHOWME();
//             break;
//         }
//         else if(commande == "SHOWME"){
//             std::cout<<DIM_TEXT<<"commande "<<commande<<" reconnue \n"<<RESET;
//             commandeSHOWME();
//         }
//         else if(commande == "DFC"){
//             std::cout<<"commande "<<commande<<" reconnue \n";
//             commandeDefausserCartes();
//         }
//         else if(commande == "ARRETJEU"){
//             std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
//             jeu.setFini(true);
//             std::cout<<BOLD_ON<<"=== ARRET DU JEU ===\n"<<RESET;
//             break;
//         }
//         else {
//             std::cout<<"commande "<<commande<<" non reconnue \n";
//         }
//     }
// }

// void Joueur::commandeDefausserCartes() {
//     std::cout<<DIM_TEXT<<"Seul les cartes dans la mains sont defaussables\n"<<RESET;
//     std::string commande = "";
//     Carte* c = nullptr;
//     commandeSHOWME();
//     while(commande != "FIN"){
//         c = demandeChercherCarte(m_main, commande);
//         if(c != nullptr){
//             if(defausserCarte(c)){
//                 std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" defaussée"<<RESET<<std::endl;
//             }
//             else{
//                 std::cout <<DIM_TEXT<<RED<< "ERROR : cartes non défaussées" << RESET<<std::endl;
//             }
//         }
//     }
// }

bool Joueur::commandePiocherCarteDeck(int quantite) {
    (void)quantite;
    // std::list<Carte*> li = piocherCarteDeck(quantite);
    // if(li.empty()){
    //     std::cout<<DIM_TEXT<<RED<<"PAS ASSEZ DE CARTE DANS LE DECK : fin de pioche\n"<<RESET;
    //     return false;
    // }
    // for(Carte* c : li){
    //     std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" piochée"<<RESET<<std::endl;
    // }
    return true;
}

void Joueur::afficherMain(bool pourPrendre, std::function<bool(Carte*)> condition, int start) {
    std::cout<<BOLD_ON<<couleurJ<< "Main:\n"<<RESET;
    Carte::afficher(m_main, pourPrendre, condition, start);
}

void Joueur::afficherUtilise() {
    std::cout<<BOLD_ON<<couleurJ<< "Cartes en cours d'utilisation:\n"<<RESET;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        std::cout << "   " << *(entry.first) << ": " << entry.second << "\n";
    }
}

void Joueur::piocher(int quantite) {
    int nbCartes = 0;
    for (const auto& paire : m_deck) {
        nbCartes += paire.second;
    }
    for(int i = 0; i<quantite; i++){
        if(m_deck.empty()){
            mettreDefausseDansDeck();
        }
        if(m_deck.empty()){
            std::cout<<DIM_TEXT<<RED<<"DECK VIDE"<<RESET<<std::endl;
        }
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
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<< entry.first -> getNom()<<" pioché"<<RESET<<std::endl;
                nbCartes -= 1;
                break;
            }
        }
    }
}