#ifndef CLASSE_HPP
#define CLASSE_HPP

#include "valeur.hpp"

/******************************************************************************/
/*                                   Classe                                   */
/******************************************************************************/

class Classe
{
public:
    /* accesseurs *************************************************************/
    unsigned getQuantite() const { return quantite; }
    void setQuantite(unsigned quantite) { this->quantite = quantite; }

    double getBorneInf() const { return borneInf; }
    void setBorneInf(double borneInf) { this->borneInf = borneInf; }

    double getBorneSup() const { return borneSup; }
    void setBorneSup(double borneSup) { this->borneSup = borneSup; }

    /* methods ****************************************************************/
    void ajouter() { quantite++; }

    bool contains(double v) const {
        return borneInf <= v && v < borneSup;
    }

    bool contains(Valeur v) const {
        return contains(v.getNombre());
    }

    /* constructeurs & destructeur ********************************************/
    Classe(double borneInf, double borneSup):
        borneInf(borneInf),
        borneSup(borneSup) {}

    Classe(const Classe& other): Classe(other.borneInf, other.borneSup) {
        quantite = other.quantite;
    }

    Classe() = default;
    ~Classe() = default;

private:
    double borneInf = 0;
    double borneSup = 0;
    unsigned long quantite = 0;
};

/******************************************************************************/
/*                                 operateurs                                 */
/******************************************************************************/

/* NOTE1: on ne prend pas en compte la quantite ici ! */

inline bool operator<(const Classe& lhs, const Classe& rhs) {
    return lhs.getBorneInf() < rhs.getBorneInf()
        && lhs.getBorneSup() < rhs.getBorneSup();
}

inline bool operator>(const Classe& lhs, const Classe& rhs) {
    return lhs.getBorneInf() > rhs.getBorneInf()
        && lhs.getBorneSup() > rhs.getBorneSup();
}

inline bool operator==(const Classe& lhs, const Classe& rhs) {
    return lhs.getBorneInf() == rhs.getBorneInf()
        && lhs.getBorneSup() == rhs.getBorneSup();
}

/******************************************************************************/
/*                                comparateur                                 */
/******************************************************************************/

template<typename T>
struct ComparateurQuantite {
    bool operator()(const T& lhs, const T& rhs) const {
        if (lhs.getQuantite() == rhs.getQuantite()) {
            // si la quantite est la même, on regarde les bornes
            return lhs.getBorneInf() < rhs.getBorneInf();
        }
        return lhs.getQuantite() > rhs.getQuantite();
    }
};

#endif
