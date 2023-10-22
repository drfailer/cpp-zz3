#include "polaire.hpp"
#include "cartesien.hpp"
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Polaire& p) {
    os << "(a=" << p.getAngle() << ";d=" << p.getDistance() << ")";
    return os;
}

void Polaire::afficher(std::ostream& os) const {
    os << *this;
}

#ifdef CAST_METHOD
void Polaire::convertir(Point& c) const {
    if (Cartesien* cc = dynamic_cast<Cartesien*>(&c)) {
        cc->setX(distance * std::cos(angle * M_PI / 180));
        cc->setY(distance * std::sin(angle * M_PI / 180));
    } else if (Polaire* pp = dynamic_cast<Polaire*>(&c)) {
        pp->setAngle(angle);
        pp->setDistance(distance);
    }
}
#else
void Polaire::convertir(Polaire& p) const {
    p.setAngle(angle);
    p.setDistance(distance);
}

void Polaire::convertir(Cartesien& c) const {
    c.setX(distance * std::cos(angle * M_PI / 180));
    c.setY(distance * std::sin(angle * M_PI / 180));
}
#endif
