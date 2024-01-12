#include "Royaume.h"

#include "CouleurTerminal.h"

#include <iostream>

Royaume::Royaume(std::string nom, int cout, std::string description)
        : Carte(nom,TypeRoyaume,cout), m_description(description) {}

Royaume::~Royaume() {}

std::string Royaume::getDescription() const {
    return m_description;
}

std::ostream& operator<<(std::ostream& os, const Royaume& royaume){
    os<< reinterpret_cast<const Carte&>(royaume);
    os<< "\tDESCRIPTION : "<<royaume.getDescription();
    return os;
}


void Royaume::jouerAction(Joueur &joueur, Jeu &jeu) {
    std::cout<<DIM_TEXT<<BOLD_ON"DESCRIPTION : "<<RESET;
    std::cout<<DIM_TEXT<<getDescription()<<"\n"<<RESET;
    faireAction(joueur, jeu);
}
void Royaume::ajoutAction(Joueur & joueur, int nb){
    joueur.addNbActionPhase(nb);
}
void Royaume::ajoutAchat(Joueur & joueur, int nb) {
    joueur.addNbAchatPhase(nb);
}
void Royaume::piocherCarteDeck(Joueur &joueur, int quantite) {
    joueur.piocherCarteDeck(quantite);
}
void Royaume::ajouterValeurSupp(Joueur &joueur, int nbValeurSupp) {
    joueur.ajouterRetirerValeurSupp(nbValeurSupp);
}
bool Royaume::recevoirCartePlateau(Joueur &joueur, Jeu &jeu, Carte* carte, int coutMax) {
    return joueur.recevoirCartePlateau(jeu,carte,coutMax);
}
void Royaume::ecarter(Joueur &joueur, Jeu &jeu, Carte* carte, int quantite) {
    joueur.ecarter(jeu,carte,quantite);
}
void Royaume::defaussPiocher(Joueur &joueur) {
    joueur.defaussPiocher();
}
void Royaume::augmenterTresor(Jeu& jeu, Joueur &joueur, int quantite) {
    joueur.augmenterTresor(jeu, quantite);
}



//////////////////////////////IHM
void Royaume::commandeRecevoirCartePlateau(Joueur& joueur, Jeu& jeu, int coutMax) {

    std::cout<<"CARTE SUR LE PLATEAU : \n";
    jeu.afficherCartesPlateau();
    std::cout<<std::endl;
    std::string commande = "";
    Carte* c = nullptr;
    while(commande != "FIN"){
        c = joueur.demandeChercherCarte(jeu.getCartesPlateau(), commande);
        if(c != nullptr){
            if(c -> getCout() <= coutMax){
                if(recevoirCartePlateau(joueur,jeu,c,coutMax)){
                    std::cout<<DIM_TEXT<<GREEN<<"carte : "<<c -> getNom()<<" recue dans la défausse"<<RESET<<std::endl;
                }
                break;
            }
            else{
                std::cout<<DIM_TEXT<<RED<<"carte : "<<c -> getNom()<<" trop chere"<<RESET<<std::endl;
            }
        }
    }
}



