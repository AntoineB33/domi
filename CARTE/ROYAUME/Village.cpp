#include "Village.h"
#include "Jeu.h"

Village* Village::instanceVillage = new Village("Marché",5," +1 Achat,  +1 Action,  +1 Carte");

Village* Village::makeVillage(){
    return Village::instanceVillage;
}
Village::~Village(){
    delete Village::instanceVillage;
}
Village::Village(std::string nom, int cout,std::string description) : Royaume(nom,cout,description){}