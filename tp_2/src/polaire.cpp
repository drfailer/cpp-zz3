#include "polaire.hpp"
#include "cartesien.hpp"
#include <iostream>
#include <cmath>

Polaire::Polaire(const Cartesien& c) {
    c.convertir(*this);
}

std::ostream& operator<<(std::ostream& os, const Polaire& p) {
    os << "(a=" << p.getAngle() << ";d=" << p.getDistance() << ")";
    return os;
}

void Polaire::afficher(std::ostream& os) const {
    os << *this;
}

void Polaire::convertir(Point& c) const {
    if (Polaire* pp = dynamic_cast<Polaire*>(&c)) {
        pp->setAngle(angle);
        pp->setDistance(distance);
    } else if (Cartesien* cc = dynamic_cast<Cartesien*>(&c)) {
        cc->setX(distance * std::cos(angle * M_PI / 180));
        cc->setY(distance * std::sin(angle * M_PI / 180));
    }
}
