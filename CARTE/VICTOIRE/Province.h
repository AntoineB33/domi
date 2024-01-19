#ifndef DOMI_PROVINCE_H
#define DOMI_PROVINCE_H

#include "Victoire.h"

class Province : public Victoire {
public:
    static Province* makeProvince();
    virtual ~Province();

    Province(Province &province) = delete;
    void operator=(const Province&) = delete;

private:
    Province(std::string, int, int);
    static Province* instanceProvince;
};


#endif //DOMI_PROVINCE_H
