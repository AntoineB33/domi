#include "Argent.h"

Argent* Argent::instanceArgent = new Argent("Argent", 3, 2);

Argent* Argent::makeArgent() {
    return Argent::instanceArgent;
}
Argent::~Argent() {
    delete Argent::instanceArgent;
}
Argent::Argent(std::string nom, int cout, int val) : Tresor(nom, cout, val){}


// std::ostream& operator<<(std::ostream& os, const Argent& argent) {
//     os << reinterpret_cast<const Tresor&>(argent);
//     return os;
// }