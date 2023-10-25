#ifndef EXPONENTIELLE_HPP
#define EXPONENTIELLE_HPP
#include "factorielle.hpp"
#include "puissance.hpp"

template<int k>
struct Exponentielle {
    static const double valeur(double x) {
        return (Puissance<k>::valeur(x) / Factorielle<k>::valeur)
               + Exponentielle<k - 1>::valeur(x);
    }
};

/* NOTE: pour pouvoir déclarer un template spécialisé comme ci-dessous
 * (`Exponentielle<0>`), il faut que le template "générique" ait été défini au
 * préalable. */
template<>
struct Exponentielle<0> {
    static const double valeur(double x) {
        return 1.0;
    }
};

#endif
