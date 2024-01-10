#ifndef PROJETCARTE_ARGENT_H
#define PROJETCARTE_ARGENT_H

#include "Tresor.h"

class Argent : public Tresor
{
public :
    static Argent* makeArgent();
    virtual ~Argent();
    friend std::ostream& operator<<(std::ostream& os, const Argent& argent);

    Argent(Argent &argent) = delete;
    void operator=(const Argent&) = delete;

private :
    Argent(std::string nom, int cout,int val);
    static Argent* instanceArgent;
};

#endif //PROJETCARTE_ARGENT_H
