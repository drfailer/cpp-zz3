#include "point.hpp"

Point::~Point() {}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    point.afficher(os);
    return os;
}
