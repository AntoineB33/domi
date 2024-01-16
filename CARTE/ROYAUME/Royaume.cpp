#include "Royaume.h"

#include "CouleurTerminal.h"

#include <iostream>

Royaume::Royaume(std::string nom, int cout, std::string description)
        : Carte(nom,TypeRoyaume,cout) {
    m_description = nom + " (Cout: " + std::to_string(cout) + ", Desc:" + description +")\n";
}

Royaume::~Royaume() {}


std::string& Royaume::getDesc() {
    return m_description;
}

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

void Royaume::ajouterValeurSupp(Joueur &joueur, int nbValeurSupp) {
    joueur.ajouterRetirerValeurSupp(nbValeurSupp);
}



//////////////////////////////IHM
void Royaume::commandeRecevoirCartePlateau(Joueur& joueur, Jeu& jeu, int coutMax) {

    jeu.afficherCartesPlateau();
    std::cout<<std::endl;
    std::string commande = "";
    Carte* c = nullptr;
    while(commande != "FIN"){
        c = jeu.demandeCartePlateau(joueur, commande);
        if(c != nullptr){
            if(c -> getCout() <= coutMax){
                if(joueur.recevoirCartePlateau(jeu,c,coutMax)){
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



