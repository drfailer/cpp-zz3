#ifndef POLAIRE_HPP
#define POLAIRE_HPP
#include "point.hpp"
#include <ostream>

class Cartesien;

class Polaire: public Point
{
public:
    /**************************************************************************/
    /* accésseurs:                                                            */
    /**************************************************************************/
    double getDistance() const { return distance; }
    double getAngle() const { return angle; }
    void setDistance(double degre) { this->distance = degre; }
    void setAngle(double anble) { this->angle = anble; }

    /**************************************************************************/
    /* méthodes:                                                              */
    /**************************************************************************/
    void afficher(std::ostream&) const override;

    #ifdef CAST_METHOD
    void convertir(Point& c) const override;
    #else
    virtual void convertir(Polaire&) const override;
    virtual void convertir(Cartesien&) const override;
    #endif

    /**************************************************************************/
    /* constructeurs & destructeurs:                                          */
    /**************************************************************************/
    Polaire(double angle, double distance): angle(angle), distance(distance) {}
    Polaire(const Point& p) { p.convertir(*this); }
    Polaire() = default;
    ~Polaire() = default;

private:
    double angle = 0;
    double distance = 0;
};

#endif
