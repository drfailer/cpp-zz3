#ifndef PUISSANCE_HPP
#define PUISSANCE_HPP

template<int p>
struct Puissance {
    static const double valeur(double n) {
        return n * Puissance<p - 1>::valeur(n);
    }
};

template<>
struct Puissance<0> {
    static const double valeur(double n) {
        return 1;
    }
};

#endif
