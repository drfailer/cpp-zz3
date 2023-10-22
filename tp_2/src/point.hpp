#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <vector>

class Point
{
public:
    virtual void afficher(std::ostream&) const = 0;
    virtual void convertir(Point& p) const = 0;
    virtual ~Point() = 0;

    using const_iterator = std::vector<Point*>::const_iterator;

private:
    std::vector<Point*> v;
};

std::ostream& operator<<(std::ostream& os, const Point& point);

#endif
