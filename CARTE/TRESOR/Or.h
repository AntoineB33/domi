#ifndef PROJETCARTE_OR_H
#define PROJETCARTE_OR_H

#include "Tresor.h"

class Or : public Tresor
{
public :
    static Or* makeOr();
    virtual ~Or();
    // friend std::ostream& operator<<(std::ostream& os, const Or& gold);

    Or(Or &o) = delete;
    void operator=(const Or&) = delete;

private :
    Or(std::string nom, int cout,int val);
    static Or* instanceOr;

};

#endif
