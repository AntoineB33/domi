#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

#include <string>

class Joueur;
class Jeu;

class Phase {
public:
    virtual ~Phase();
    static Phase* getInstance();
    virtual Phase* getPhaseSuivante() = 0;
    const std::string* getNomPhase() const;


    /// IHM
    virtual void jouerPhase(Jeu& jeu, Joueur& joueur) = 0;

protected:
    Phase(std::string nomPhase);
    void afficherPhase(Joueur& joueur);


private:
    const std::string m_nomPhase;
    static Phase* instance;
};


#endif //DOMI_PHASE_H
