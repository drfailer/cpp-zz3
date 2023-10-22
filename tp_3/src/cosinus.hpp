#ifndef COSINUS_HPP
#define COSINUS_HPP
#include "factorielle.hpp"
#include "puissance.hpp"

/******************************************************************************/
/*                                  cosinus                                   */
/******************************************************************************/

template<int k>
struct Cosinus {
    static const double valeur(double x) {
        return (k%2 ? -1:1)
               * Puissance<2*k>::valeur(x) / Factorielle<2*k>::valeur
               + Cosinus<k - 1>::valeur(x);
    }
};

template<>
struct Cosinus<0> {
    static const double valeur(double x) {
        return 1.0;
    }
};

/******************************************************************************/
/*                                   sinus                                    */
/******************************************************************************/

template<int k>
struct Sinus {
    static const double valeur(double x) {
        return (k%2 ? -1:1)
               * Puissance<2*k + 1>::valeur(x) / Factorielle<2*k + 1>::valeur
               + Sinus<k - 1>::valeur(x);
    }
};

template<>
struct Sinus<0> {
    static const double valeur(double x) {
        return x;
    }
};

#endif
