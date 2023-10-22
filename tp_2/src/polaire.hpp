#ifndef POLAIRE_HPP
#define POLAIRE_HPP
#include "point.hpp"
#include <ostream>

class Cartesien;

class Polaire: public Point
{
public:
    double getDistance() const { return distance; }
    double getAngle() const { return angle; }
    void setDistance(double degre) { this->distance = degre; }
    void setAngle(double anble) { this->angle = anble; }
    void afficher(std::ostream&) const override;
    void convertir(Point& c) const override;
    Polaire(double angle, double distance): angle(angle), distance(distance) {}
    Polaire(const Cartesien& c);
    Polaire() = default;
    ~Polaire() = default;

private:
    double angle = 0;
    double distance = 0;
};

#endif
