#include "Joueur.h"
#include "Jeu.h"

#include <random>

#include <iostream>
#include <ostream>
#include <algorithm>


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

Joueur::Joueur(const int numJoueur) :m_numJoueur(numJoueur), m_nbAchatPossible(0), m_nbActionPossible(0) , m_valeurSupp(0){
    couleurJ =  "\033["+std::to_string(m_numJoueur+33)+"m";
}

Joueur::~Joueur() {
    m_deck.clear();
    m_defausse.clear();
    m_main.clear();
    m_carteEnCoursDutilisation.clear();

}

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
void Joueur::prendreCartePlateau(Carte* carte, Jeu& jeu, int quantite, bool gratuit, bool depuisLaReserve) {
    if(!gratuit){
        prendreArgent(carte -> getCout());
    }
    Carte::ajoutSuppCarte(m_deck, carte, quantite);
    if(depuisLaReserve) {
        jeu.retirerCarteDisponible(carte, quantite);
    }
}




///////////////////////////////////////ACTION DU JOUEUR
bool Joueur::acheterCarte(Carte* carte, Jeu& jeu){
    if(peutAcheterCarte(carte, jeu)) {
        prendreCartePlateau(carte, jeu);
        m_nbAchatPossible -= 1;
        return true;
    }
    return false;
}
bool Joueur::jouerCarteAction(Carte* c, Jeu& jeu){
    auto it = m_carteEnCoursDutilisation.find(c);
    if(it != m_carteEnCoursDutilisation.end()){
        if( c -> getTypeCarte() == TypeRoyaume){
            c -> jouerAction(*this, jeu);
            //on retire la carte
            if(Carte::ajoutSuppCarte(m_carteEnCoursDutilisation,c,-1)){
                Carte::ajoutSuppCarte(m_defausse,c,1);
            }
            m_nbActionPossible -= 1;
            return true;
        }
    }
    return false;
}
bool Joueur::ajuster(){
    size_t q = 5;
    //vider
    defausserCarte();

    //piocher
    if(m_deck.size() < q){
        piocherCarteDeck(m_deck.size());
        q -= m_deck.size();
        if(m_deck.size() < 5) {
            mettreCarteDefausseDansDeck();
        }
        piocherCarteDeck(q);
    }
    else{
        piocherCarteDeck(q);
    }
    return true;
}

int Joueur::getVictoireDansDeck(){
    defausserCarte();
    mettreCarteDefausseDansDeck();
    int nb = 0;
    for(auto entry : m_deck){
        if(entry.first -> getTypeCarte() == TypeVictoire){
            nb += entry.first -> getPointDeVictoire();
        }
    }
    return nb;
}

///////////////////////////////////////ACTION DU JOUEUR VIA UNE CARTE ACTION
bool Joueur::recevoirCartePlateau(Jeu& jeu, Carte* carte, int quantite) {
    if(jeu.retirerCarteDisponible(carte,quantite)) {
        return Carte::ajoutSuppCarte(m_defausse,carte,quantite);
    }
    return false;
}

bool Joueur::ecarter(Jeu& jeu, Carte* carte, int quantite){
    for(int i = 0; i < quantite; i++ ){
        if(!mettreDansRebus(jeu, carte)){
            return false;
        }
    }
    return true;
}

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
    std::cout<<"ajout valeur supp : "<<nbValeurSup<<std::endl;
    m_valeurSupp += nbValeurSup;
}








///////////////////////////////////////FONCTION PRIVATE

int Joueur::nbPointVictoire() {
    int nb = 0;
    for(auto entry : m_main){
        if(entry.first -> getTypeCarte() == TypeVictoire){
            nb += entry.first -> getValeur();
        }
    }
    for(auto entry : m_carteEnCoursDutilisation){
        if(entry.first -> getTypeCarte() == TypeVictoire){
            nb += entry.first -> getValeur();
        }
    }
    for(auto entry : m_deck){
        if(entry.first -> getTypeCarte() == TypeVictoire){
            nb += entry.first -> getValeur();
        }
    }
    for(Carte* c : m_defausse){
        if(c -> getTypeCarte() == TypeVictoire){
            nb += c -> getValeur();
        }
    }
    return nb;
}

int Joueur::nbValeurDisponible() const {
    int val = m_valeurSupp;
    for (const auto& entry : m_carteEnCoursDutilisation) {
        val += entry.second * (entry.first -> getValeur());
    }
    return val;
}
bool Joueur::peutAcheterCarte(Carte* carte, Jeu jeu){
    // il faut que le carte soit encore disponible a l'achat
    bool b = jeu.carteDisponible(carte);
    if(!b){
        //std::cout<<"PAS DISPO"<<std::endl;
        return false;
    }
    // que le joueur est l'argent necessaire
    b = b && nbValeurDisponible() >= carte -> getCout();
    if(!b){
        //std::cout<<"PAS ASSEZ ARGENT"<<std::endl;
        return false;
    }
    // que le joueur est au moins un point d'achat
    b =b && m_nbAchatPossible > 0;
    if(!b){
        //std::cout<<"PAS D ACHAT POSSIBLE"<<std::endl;
        return false;
    }
    return   b;
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
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<<entry.first -> getNom()<<" piochée"<<RESET<<std::endl;
                Carte::ajoutSuppCarte(m_deck,entry.first, -1);
                Carte::ajoutSuppCarte(m_main,entry.first, 1);
                quantite -= 1;
                void supprimerCarteMain(Carte* c, int quantite = 1);
                void addNbAchatPhase(int nbAchatPhase);
                void addNbActionPhase(int nbActionPhase);

                nbCartes -= 1;
                break;
            }
        }
    }
    if(quantite !=0){
        //PB
    }

}

bool Joueur::mettreDansRebus(Jeu& jeu, Carte *carte) {
    if(Carte::ajoutSuppCarte(m_main, carte, -1)){
        jeu.mettreDansRebus(carte);
        return true;
    }
    return false;
}

bool Joueur::defausserCarte(Carte *carte) {

    if(Carte::ajoutSuppCarte(m_main, carte, -1)){
        Carte::ajoutSuppCarte(m_defausse, carte, 1);
        return true;
    }
    return false;
}

bool Joueur::defausserCarte() {//defausser tout
    for(auto entry : m_main){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_main.clear();
    for(auto entry : m_carteEnCoursDutilisation){
        Carte::ajoutSuppCarte(m_defausse, entry.first, entry.second);
    }
    m_carteEnCoursDutilisation.clear();
    return true;
}

bool Joueur::mettreEncoursDutilisationCartes(Carte* carte, int quantite) {
    if(Carte::ajoutSuppCarte(m_main, carte, -quantite)){
        return Carte::ajoutSuppCarte(m_carteEnCoursDutilisation, carte, quantite);
    }
    return false;
}



bool Joueur::mettreCarteDefausseDansDeck(){
    if(m_deck.size() < 5){
        for(Carte* c : m_defausse){
            Carte::ajoutSuppCarte(m_deck,c,1);
        }
        m_defausse.clear();
        return true;
    }
    return false;
}







///////////////////////////////////////TOUR D UN JOUEUR + IHM
void Joueur::tourJoueur(Jeu& jeu){
    std::cout<<BLINK_ON<<BOLD_ON<<couleurJ<<"\n\n=============================================\n";
    std::cout<<"=============== TOUR JOUEUR "<<m_numJoueur<<" ===============\n";
    std::cout<<"=============================================\n\n"<<RESET<<std::endl;
    while(!jeu.estAPhaseAjustement() && !jeu.getFini()){
        std::cout<<BOLD_ON<<INVERSE_ON<<couleurJ<<*jeu.getNomPhaseActu()<<RESET<<"\n";
        jeu.initJoueurPhase(*this);
        commandeSHOWME();
        // ACTION DU JOUEUR
        jouerPhase(jeu);
        //
        jeu.changementDePhase();
    }
    if(!jeu.commandePartieEstFinie()){
        std::cout<<BOLD_ON<<INVERSE_ON<<couleurJ<<*jeu.getNomPhaseActu()<<RESET<<"\n";
        jeu.initJoueurPhase(*this);
        commandeSHOWME();
        // AJUSTEMET DU JOUEUR
        faireAjustement(jeu);
        //
        jeu.changementDePhase();
    }

}

void Joueur::jouerPhase(Jeu& jeu){
    std::string commande = " ";
    while(commande != "FIN"){
        std::cout<<std::endl;
        std::cout<<BOLD_ON<<couleurJ<<"\n==> ECRIRE COMMANDE\n"<<RESET;
        std::cout<<DIM_TEXT<<"possibilité d'écrire la commande : "<<UNDERLINE_ON<<"HELP\n"<<RESET;
        std::cin>>commande;
        if(commande == "HELP"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeHELP();
        }
        else if(commande == "FIN"){
            break;
        }
        else if(commande == "SHOWME"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeSHOWME();
        }
        else if(commande =="ACHAT") {
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeAchat(jeu);
        }
        else if (commande == "ACTION"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeJoueur(jeu);
        }
        else if(commande == "UTILISER"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeMettreCarteUtilisation();
        }
        else if(commande == "GODMODE"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeGODMODE(jeu);
        }
        else if(commande == "ARRETJEU"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            jeu.setFini(true);
            std::cout<<BOLD_ON<<"=== ARRET DU JEU ===\n"<<RESET;
            break;
        }
        else {
            std::cout<<DIM_TEXT<<RED<<"commande "<<commande<<UNDERLINE_ON<<" non reconnue \n"<<RESET;
        }
    }

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
Carte* Joueur::demandeChercherCarte(std::map<Carte*,int> m, std::string &commande) {
    Carte* c = nullptr;
    std::cout<<"ECRIRE NOM CARTE\n";
    std::cin>> commande;
    if(commande == "FIN"){
        return c;
    }
    c = Carte::chercherCarte(commande,m);
    if(c == nullptr){
        std::cout<<DIM_TEXT<<RED<<"carte : "<<commande<<" NON TROUVEE"<<RESET<<std::endl;
    }
    return c;
}
int Joueur::demandeQuantiteCarte(std::map<Carte*,int> m,Carte* c ,std::string &commande){
    auto it = m.find(c);
    if(it== m.end()){
        std::cout<<"ERREUR CARTE INEXISTANTE\n";
        return 0;
    }
    int q = -1;
    int nbMAX = it -> second;
    while(1){
        std::cout<<"QUANTITE VOULUE : "<<DIM_TEXT<<ITALIC_ON<<"(attention aux espaces)\n";
        std::cout<<DIM_TEXT<<ITALIC_ON<<"(TOUT\tprend la quantité maximal disponible)\n"<<RESET;
        std::cin>> commande;
        //cas pécifique
        if(commande == "TOUT"){
            return nbMAX;
        }
        else if(commande =="FIN"){
            return 0;
        }

        try {
            q = std::stoi(commande);
        }
        catch (std::invalid_argument const &e) {
            std::cout <<DIM_TEXT<<RED<< "ERROR : entree invalide" << RESET<<std::endl;
        }
        catch (std::out_of_range const &e) {
            std::cout << DIM_TEXT<<RED<<"ERROR : nombre trop grand"<<RESET<< std::endl;
        }

        //verification : arret de la boucle ?
        if(!(0<= q  && q <= nbMAX)){
            std::cout << DIM_TEXT<<RED<<"ERROR : nombre non compris entre 0 et quantite disponible : "<< nbMAX <<RESET<< std::endl;
        }
        else{
            return q;
        }
    }
    return 0;
}

int Joueur::commandeEcarter(Jeu& jeu, int quantite) {
    int cout = 0;
    for(int i = 0; i< quantite; i++) {
        std::cout<<DIM_TEXT<<"Seuls les cartes dans la main sont défaussables\n"<<RESET;
        std::string commande = "";
        Carte* c = nullptr;
        commandeSHOWME();
        while(1){
            c = demandeChercherCarte(m_main, commande);
            if(c != nullptr){
                ecarter(jeu,c,1);
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" écarté"<<RESET<<std::endl;
                cout = c -> getCout();
                break;
            }
            if(commande == "FIN"){
                break;
            }
        }
    }
    return cout;
}

void Joueur::defaussPiocher(){
    std::string commande = " ";
    while(commande != "FIN"){
        std::cout<<std::endl;
        std::cout<<DIM_TEXT<<"possibilité de défausser : "<<RESET;
        Carte* c = demandeChercherCarte(m_main, commande);
        if(c != nullptr) {
            defausserCarte(c);
            piocherCarteDeck(1);
            break;
        }
    }
}

void Joueur::augmenterTresor(Jeu& jeu, int quantite){
    std::string commande = " ";
    while(commande != "FIN"){
        std::cout<<std::endl;
        std::cout<<DIM_TEXT<<"augmentez une carte Trésor : "<<RESET;
        Carte* c = demandeChercherCarte(m_main, commande);
        if(c != nullptr && c -> getTypeCarte() == TypeTresor) {
            defausserCarte(c);
            while(commande != "FIN") {
                std::cout<<std::endl;
                std::cout<<DIM_TEXT<<"Prenez une carte Trésor de la réserve : "<<RESET;
                c = demandeChercherCarte(jeu.getCartesPlateau(), commande);
                if(c != nullptr && c -> getTypeCarte() == TypeTresor && c -> getCout() <= quantite) {
                    jeu.retirerCarteDisponible(c,1);
                    break;
                }
            }
            break;
        }
    }
}

void Joueur::commandeAchat(Jeu &jeu){
    std::cout<<"CARTE SUR LE PLATEAU : \n";
    jeu.afficherCartesPlateau();
    std::cout<<std::endl;
    std::string commande = "";
    Carte* c = nullptr;
    while(commande != "FIN"){
        if(m_nbAchatPossible <= 0){
            std::cout<<DIM_TEXT<<RED<<"PAS ASSEZ DE POINT D ACHAT : fin d'achat\n"<<RESET;
            break;
        }
        c = demandeChercherCarte(jeu.getCartesPlateau(), commande);
        if(c != nullptr){
            if(acheterCarte(c,jeu)){
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" achetee "<<RESET<<std::endl;
            }
            else{
                std::cout<<DIM_TEXT<<RED<<"impossible d'acheter carte : "<<commande<<RESET<<std::endl;
            }
        }
    }
}
void Joueur::commandeJoueur(Jeu &jeu){
    std::cout<<"CARTE EN COURS D UTILISATION : \n";
    Carte::afficher(m_carteEnCoursDutilisation);
    std::cout<<std::endl;
    std::string commande = "";
    Carte* c = nullptr;
    while(commande != "FIN"){
        if(m_nbActionPossible <= 0){
            std::cout<<DIM_TEXT<<RED<<"PAS ASSEZ DE POINT D ACTION : fin d'action\n"<<RESET;
            break;
        }
        c = demandeChercherCarte(m_carteEnCoursDutilisation, commande);
        if(c != nullptr){
            if(jouerCarteAction(c, jeu)){
                std::cout<<DIM_TEXT<<GREEN<<"carte jouer\n"<<RESET;
            }
            else{
                std::cout<<DIM_TEXT<<RED<<"ne pas faire l'action\n";
                std::cout<<ITALIC_ON<<"(ce n'est peut etre pas une carte Action ou est dans les cartes en cours d utilisation)\n"<<RESET;
            }

        }
    }
}
void Joueur::commandeMettreCarteUtilisation() {
    std::string commande = "";
    Carte* c = nullptr;
    int q;
    commandeSHOWME();
    while(commande != "FIN"){
        c = demandeChercherCarte(m_main, commande);
        if(c != nullptr){
            q = demandeQuantiteCarte(m_main, c, commande);
            if(mettreEncoursDutilisationCartes(c,q)){
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" mise en cours d'utilisation"<<RESET<<std::endl;
            }
        }
    }
}
void Joueur::commandeGODMODE(Jeu& jeu){
    int nbPioche = 0;
    for(std::pair<Carte*, int> p : jeu.getCartesPlateau()){
        prendreCartePlateau(p.first, jeu, 10, true, true);
        nbPioche += 10;
    }
    piocherCarteDeck(nbPioche);
    m_nbAchatPossible += nbPioche;
    m_nbActionPossible += nbPioche;
    std::cout<<BOLD_ON<<DIM_TEXT<<"=== GOD MODE ===\n"<<RESET;
}
void Joueur::faireAjustement(Jeu& jeu) {
    std::string commande = " ";
    while(commande != "FIN"){
        std::cout<<BOLD_ON<<couleurJ<<"\n==> ECRIRE COMMANDE\n"<<RESET;
        std::cout<<DIM_TEXT<<"possibilité d'écrire la commande : HELP\n"<<RESET;
        std::cout<<DIM_TEXT<<"en phase ajustement, la commande : FIN, défausse automatiquement toutes les cartes et pioche les cartes\n"<<RESET;
        std::cin>> commande;
        if(commande == "HELP"){
            commandeHELP();
        }
        else if(commande == "FIN"){
            ajuster();
            commandeSHOWME();
            break;
        }
        else if(commande == "SHOWME"){
            std::cout<<DIM_TEXT<<"commande "<<commande<<" reconnue \n"<<RESET;
            commandeSHOWME();
        }
        else if(commande == "DFC"){
            std::cout<<"commande "<<commande<<" reconnue \n";
            commandeDefausserCartes();
        }
        else if(commande == "ARRETJEU"){
            std::cout<<DIM_TEXT<<GREEN<<"commande "<<commande<<" reconnue \n"<<RESET;
            jeu.setFini(true);
            std::cout<<BOLD_ON<<"=== ARRET DU JEU ===\n"<<RESET;
            break;
        }
        else {
            std::cout<<"commande "<<commande<<" non reconnue \n";
        }
    }
}
void Joueur::commandeDefausserCartes() {
    std::cout<<DIM_TEXT<<"Seul les cartes dans la mains sont defaussables\n"<<RESET;
    std::string commande = "";
    Carte* c = nullptr;
    commandeSHOWME();
    while(commande != "FIN"){
        c = demandeChercherCarte(m_main, commande);
        if(c != nullptr){
            if(defausserCarte(c)){
                std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" defaussée"<<RESET<<std::endl;
            }
            else{
                std::cout <<DIM_TEXT<<RED<< "ERROR : cartes non défaussées" << RESET<<std::endl;
            }
        }
    }
}
