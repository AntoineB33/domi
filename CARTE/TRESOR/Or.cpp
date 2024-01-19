#include "Or.h"
#include "Tresor.h"

Or* Or::instanceOr = new Or("Or", 6, 3);


Or* Or::makeOr() {
    return Or::instanceOr;
}


Or::~Or() {
    delete Or::instanceOr;
}

Or::Or(std::string nom, int cout, int val) : Tresor(nom, cout, val){}

// std::ostream& operator<<(std::ostream& os, const Or& gold){
//     os<< reinterpret_cast<const Tresor&>(gold);
//     return os;
// }
