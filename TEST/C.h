//
// Created by moi on 03/01/24.
//

#ifndef DOMI_C_H
#define DOMI_C_H

#include "A.h"

class C : public A{
    void calcul(int*& a) override;
private :
    int a;
};


#endif //DOMI_C_H
