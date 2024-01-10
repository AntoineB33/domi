#include <iostream>
#include "A.h"

#include "C.h"
int main(){
    A* a = nullptr;
    C c = C();
    int aa = 3;
    int* aaa = &aa;
    a = &c;

    a -> calcul(aaa);
    std::cout<<*aaa<<"\n\n\n";

    return 0;
}
