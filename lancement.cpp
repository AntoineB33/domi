#include <iostream>

#include "Jeu.h"
#include "CouleurTerminal.h"


int demandeNBJoueur(){
    int  q = 1;
    std::string commande;
    while(1){
        std::cout<<"NOMBRE DE JOUEUR : \n";
        std::cout<<DIM_TEXT<<ITALIC_ON<<"(de 2 à 4 joueurs)\n"<<RESET;
        std::cin>> commande;
        try {
            q = std::stoi(commande);
            if(2<=q && q <=4){
                std::cout << DIM_TEXT<<GREEN<<"nombre de joueurs demandé :"<<q<<RESET<< std::endl;
                return q;
            }
            else{
                std::cout <<DIM_TEXT<<RED<< "ERROR : nombre non compris entre 2 et 4" << RESET<<std::endl;
            }
        }
        catch (std::invalid_argument const &e) {
            std::cout <<DIM_TEXT<<RED<< "ERROR : entree invalide" << RESET<<std::endl;
        }
        catch (std::out_of_range const &e) {
            std::cout << DIM_TEXT<<RED<<"ERROR : nombre trop grand"<<RESET<< std::endl;
        }
    }
}
bool demandeSiNouvellePartie(){
    std::string commande;
    while(1){
        std::cout<<"VOULEZ VOUS LANCER UNE PARTIE ? \n";
        std::cout<<DIM_TEXT<<ITALIC_ON<<"(repondre O pour OUI, N pour NON)\n"<<RESET;
        std::cin>> commande;
        if(caseInsensitiveCompare(commande, "OUI") || caseInsensitiveCompare(commande, "O")){
            return true;
        }
        else if(caseInsensitiveCompare(commande, "NON") || caseInsensitiveCompare(commande, "N")){
            return false;
        }
        else{
            std::cout << DIM_TEXT<<RED<<"ERROR : demande non reconnue"<<RESET<< std::endl;
        }

    }
}

int main() {
    int nbJoueur;
    do{
        nbJoueur = demandeNBJoueur();
        Jeu j = Jeu(nbJoueur);
        j.lancementJeu();

    }while(demandeSiNouvellePartie());
    std::cout<<"\n\n\n\n====== FIN ======\n\n\n\n";
    return 0;
}