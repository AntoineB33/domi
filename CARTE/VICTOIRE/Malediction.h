#ifndef DOMI_MALEDICTION_H
#define DOMI_MALEDICTION_H

#include "Victoire.h"

class Malediction : public Victoire {
public:
    static Malediction* makeMalediction();
    virtual ~Malediction();

    Malediction(Malediction &malediction) = delete;
    void operator=(const Malediction&) = delete;

private:
    Malediction(std::string, int, int);
    static Malediction* instanceMalediction;
};


#endif //DOMI_MALEDICTION_H
