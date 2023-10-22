#include "cartesien.hpp"
#include "polaire.hpp"
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Cartesien& p) {
    os << "(x=" << p.getX() << ";y=" << p.getY() << ")";
    return os;
}

void Cartesien::afficher(std::ostream& os) const {
    os << *this;
}

#ifdef CAST_METHOD
void Cartesien::convertir(Point& p) const {
    if (Cartesien* cc = dynamic_cast<Cartesien*>(&p)) {
        cc->setX(x);
        cc->setY(y);
    } else if (Polaire* pp = dynamic_cast<Polaire*>(&p)) {
        pp->setAngle(std::atan2(y, x) * 180 / M_PI);
        pp->setDistance(std::hypot(x, y));
    }
}
#else
void Cartesien::convertir(Polaire& p) const {
    p.setAngle(std::atan2(y, x) * 180 / M_PI);
    p.setDistance(std::hypot(x, y));
}

void Cartesien::convertir(Cartesien& c) const {
    c.setX(x);
    c.setY(y);
}
#endif
