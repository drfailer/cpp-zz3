#ifndef USINECARTE_HPP
#define USINECARTE_HPP
#include "carte.hpp"
#include <memory>

class UsineCarte
{
    public:
        int getCpt_max() const { return cpt_max; }
        std::unique_ptr<Carte> getCarte() {
            if (cpt < cpt_max) {
                return std::unique_ptr<Carte>(new Carte(cpt++));
            }
            return nullptr;
        }
        UsineCarte() = default;
        UsineCarte(int cpt_max): cpt_max(cpt_max) {}
        ~UsineCarte() = default;

    UsineCarte(const UsineCarte&) = delete;
    UsineCarte& operator=(const UsineCarte&) = delete;

private:
    int cpt = 0;
    int cpt_max = 52;
};

#endif
