#ifndef FACTORIELLE_HPP
#define FACTORIELLE_HPP

template<int i>
struct Factorielle {
    static const long valeur = i * Factorielle<i - 1>::valeur;
};

template<>
struct Factorielle<0> {
    static const long valeur = 1;
};

#endif
