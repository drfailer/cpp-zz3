#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP
#include <vector>
#include <iostream>
#include <memory>

class Ressource
{
public:
    int getStock() const { return stock; }
    void consommer(int nb_ressource) {
        stock -= nb_ressource;
        if (stock < 0) stock = 0;
    }

    Ressource(int stock_init): stock(stock_init) {}
    ~Ressource() = default;

private:
    int stock = 0;
};

using ressources_t = std::vector<std::weak_ptr<Ressource>>;

inline std::ostream& operator<<(std::ostream& os, const ressources_t& ressources) {
    for (std::weak_ptr<Ressource> r : ressources) {
        if (std::shared_ptr<Ressource> rr = r.lock()) {
            os << rr->getStock();
        } else {
            os << "-";
        }
        os << " ";
    }
    return os;
}

#endif
