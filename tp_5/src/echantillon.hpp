#ifndef ECHANTILLON_HPP
#define ECHANTILLON_HPP
#include "valeur.hpp"
#include <algorithm>

#include <stdexcept>
#include <vector>
class Echantillon
{
public:
    /* accesseurs *************************************************************/
    void ajouter(Valeur v) { valeurs.push_back(v); }
    int getTaille() const { return valeurs.size(); }
    Valeur getValeur(int index) const { return valeurs.at(index); }

    /* min & max **************************************************************/
    Valeur getMinimum() const {
        if (valeurs.size() <= 0) {
            throw std::domain_error("no valeurs");
        }
        return *std::min_element(valeurs.begin(), valeurs.end());
    }

    Valeur getMaximum() const {
        if (valeurs.size() <= 0) {
            throw std::domain_error("no valeurs");
        }
        return *std::max_element(valeurs.begin(), valeurs.end());
    }

    /* iterator ***************************************************************/
    using iterator = std::vector<Valeur>::iterator;
    using const_iterator = std::vector<Valeur>::const_iterator;
    iterator begin() { return valeurs.begin(); }
    iterator end() { return valeurs.end(); }
    const_iterator begin() const { return valeurs.begin(); }
    const_iterator end() const { return valeurs.end(); }

    /* constructeurs & destructeur ********************************************/
    Echantillon() = default;
    ~Echantillon() = default;

private:
    std::vector<Valeur> valeurs;
};

#endif
