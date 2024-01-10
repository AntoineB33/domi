#ifndef DOMI_CUIVRE_H
#define DOMI_CUIVRE_H

#include "Tresor.h"
#include "Carte.h"

class Cuivre : public Tresor {
public:
    static Cuivre* makeCuivre();
    static Carte* getCarte();
    virtual ~Cuivre();
    friend std::ostream& operator<<(std::ostream& os, const Cuivre& cuivre);

    Cuivre(Cuivre &argent) = delete;
    void operator=(const Cuivre&) = delete;

private:
    Cuivre(std::string nom, int cout, int val);
    static Cuivre* instanceCuivre;
};

#endif //DOMI_CUIVRE_H
