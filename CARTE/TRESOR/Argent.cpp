#include "Argent.h"

Argent* Argent::instanceArgent = new Argent("Argent", 3, 2);

Argent* Argent::makeArgent() {
    return Argent::instanceArgent;
}
Argent::~Argent() {
    delete Argent::instanceArgent;
}
Argent::Argent(std::string nom, int cout, int val) : Tresor(nom, cout, val){}