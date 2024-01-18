#ifndef DOMI_PHASE_H
#define DOMI_PHASE_H

#include <string>

class Joueur;
class Jeu;

class Phase {
public:

    virtual ~Phase() = default;
    virtual Phase& getPhaseSuivante() = 0;


    /// IHM
    virtual void jouerPhase(Jeu& jeu, Joueur& joueur) = 0;
    virtual const std::string& getNomPhase() const;
    virtual bool dernierePhase() const;

protected:
    // Phase(std::string nomPhase);
    void afficherPhase(Joueur& joueur);
    // static Phase* instance;


private:
    std::string m_nomPhase;
};


#endif //DOMI_PHASE_H
