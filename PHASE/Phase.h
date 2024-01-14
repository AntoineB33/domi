#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

class Jeu;

class Phase {
public:
    Phase(int nbINITachat, int nbINITaction);
    virtual ~Phase();
    virtual Phase* phaseSuivante() = 0;

    static Phase* getPhaseCourante();
    void initJeu(Jeu &jeu);

protected:
    static Phase* phaseCourante;


private:
    const int m_nbINITachat;
    const int m_nbINITaction;
};


#endif //DOMI_PHASE_H
