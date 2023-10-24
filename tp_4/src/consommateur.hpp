#ifndef CONSOMMATEUR_HPP
#define CONSOMMATEUR_HPP
#include "ressource.hpp"
#include <memory>

class Consommateur
{
public:
    void puiser() {
        if (r != nullptr) {
            r->consommer(besoin);
            if (r->getStock() <= 0) {
                r = nullptr;
            }
        }
    }

    Consommateur(int besoin, std::shared_ptr<Ressource> r): besoin(besoin), r(r) {}
    ~Consommateur() = default;

private:
    int besoin;
    std::shared_ptr<Ressource> r;
};

#endif
