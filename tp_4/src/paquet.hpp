#ifndef PAQUET_HPP
#define PAQUET_HPP
#include <memory>
#include <vector>
#include <ostream>
#include "carte.hpp"
#include "usine.hpp"

using paquet_t = std::vector<std::unique_ptr<Carte>>;

inline void remplir(paquet_t& paquet, UsineCarte& usine) {
    for (int i = 0; i < usine.getCpt_max(); ++i) {
        paquet.push_back(usine.getCarte());
    }
}

inline std::ostream& operator<<(std::ostream& os, paquet_t& paquet) {
    for (auto& carte : paquet) {
        os << carte->getValeur() << " ";
    }
    return os;
}

#endif
