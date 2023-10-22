#ifndef CARTESION_HPP
#define CARTESION_HPP
#include "point.hpp"
#include <ostream>

class Polaire;

class Cartesien: public Point
{
public:
    void setY(double y) { this->y = y; }
    void setX(double x) { this->x = x; }
    double getY() const { return y; }
    double getX() const { return x; }
    void afficher(std::ostream&) const override;
    void convertir(Point& p) const override;
    Cartesien(double x, double y): x(x), y(y) { }
    Cartesien(const Polaire& p);
    Cartesien() = default;
    ~Cartesien() = default;

private:
    double x = 0;
    double y = 0;
};

#endif
