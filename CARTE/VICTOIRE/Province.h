//
// Created by moi on 22/12/23.
//

#ifndef DOMI_PROVINCE_H
#define DOMI_PROVINCE_H

#include "Victoire.h"

class Province : public Victoire {
public:
    static Province* makeProvince();
    virtual ~Province();
    friend std::ostream& operator<<(std::ostream& os, const Province& province);

    Province(Province &province) = delete;
    void operator=(const Province&) = delete;

private:
    Province(std::string, int, int);
    static Province* instanceProvince;
};


#endif //DOMI_PROVINCE_H
