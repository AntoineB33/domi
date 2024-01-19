#ifndef __TRESOR_H
#define __TRESOR_H

#include <string>
#include "Carte.h"

class Tresor : public Carte
{
public:
    Tresor(std::string nom, int cout,int val);
    ~Tresor();

    int getValeur() const override;

private:
    int m_valeur;

};

#endif
