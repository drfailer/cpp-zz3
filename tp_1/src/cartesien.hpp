#ifndef CARTESION_HPP
#define CARTESION_HPP
#include "point.hpp"
#include <ostream>

class Polaire;

class Cartesien: public Point
{
public:
    /**************************************************************************/
    /* accésseurs:                                                            */
    /**************************************************************************/
    void setY(double y) { this->y = y; }
    void setX(double x) { this->x = x; }
    double getY() const { return y; }
    double getX() const { return x; }

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
    Cartesien(double x, double y): x(x), y(y) { }
    Cartesien(const Point& p) { p.convertir(*this); }
    Cartesien() = default;
    ~Cartesien() = default;

private:
    double x = 0;
    double y = 0;
};

#endif
