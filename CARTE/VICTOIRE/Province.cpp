#include "Province.h"

Province* Province::instanceProvince = new Province("Province", 8, 6);

Province* Province::makeProvince() {
    return instanceProvince;
}

Province::~Province() {
    delete Province::instanceProvince;
}

Province::Province(std::string nom, int cout, int point) : Victoire(nom, cout, point) {}