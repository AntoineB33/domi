#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

class Jeu; //sinon boucle dans les include ".h"

class Phase {
public:
    Phase(int nbMAxachat, int nbMAXaction);
    virtual ~Phase();
    virtual Phase* phaseSuivante() = 0;

    void initialiseNbAchatNbAction(Jeu& jeu);

private:
    const int m_nbMAXachat;
    const int m_nbMAXaction;
};


#endif //DOMI_PHASE_H
