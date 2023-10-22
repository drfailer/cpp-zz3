#include "cartesien.hpp"
#include "polaire.hpp"
#include <iostream>
#include <cmath>
#include <memory>

Cartesien::Cartesien(const Polaire& p) {
    p.convertir(*this);
}

std::ostream& operator<<(std::ostream& os, const Cartesien& p) {
    os << "(x=" << p.getX() << ";y=" << p.getY() << ")";
    return os;
}

void Cartesien::afficher(std::ostream& os) const {
    os << *this;
}

void Cartesien::convertir(Point& p) const {
    if (Polaire* pp = dynamic_cast<Polaire*>(&p)) {
        pp->setAngle(std::atan2(y, x) * 180 / M_PI);
        pp->setDistance(std::hypot(x, y));
    } else if (Cartesien* cc = dynamic_cast<Cartesien*>(&p)) {
        cc->setX(x);
        cc->setY(y);
    }
}

