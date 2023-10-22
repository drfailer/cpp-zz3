#ifndef NUAGE_HPP
#define NUAGE_HPP
#include "point.hpp"
#include "cartesien.hpp"
#include "polaire.hpp"
#include <vector>

template<typename T>
class Nuage
{
public:
    Nuage() = default;
    ~Nuage() = default;
    void ajouter(T p) {
        points.push_back(p);
    }
    int size() const {
        return points.size();
    }
    using const_iterator = typename std::vector<T>::const_iterator;
    const_iterator begin() const { return points.cbegin(); }
    const_iterator end() const { return points.cend(); }

private:
    std::vector<T> points;
};

template<typename T>
T barycentre_v1(Nuage<T> n) {
    T output;
    Polaire c;
    double sum_Angle = 0;
    double sum_Distance = 0;

    for (T p : n) {
        p.convertir(c);
        sum_Angle += c.getAngle();
        sum_Distance += c.getDistance();
    }
    Polaire((n.size())? sum_Angle / n.size() : 0.0,
              (n.size())? sum_Distance / n.size() : 0.0)
        .convertir(output);
    return output;
}

template<template<typename> class Container, typename T>
T barycentre_v2(Container<T> n) {
    T output;
    Cartesien c;
    double sum_x = 0;
    double sum_y = 0;

    for (T p : n) {
        p.convertir(c);
        sum_x += c.getX();
        sum_y += c.getY();
    }
    Cartesien((n.size())? sum_x / n.size() : 0.0,
              (n.size())? sum_y / n.size() : 0.0)
        .convertir(output);
    return output;
}

/******************************************************************************/
/*                                 foncteurs                                  */
/******************************************************************************/

struct BarycentreCartesien {
    Cartesien operator()(Nuage<Cartesien> n) {
        double sum_x = 0;
        double sum_y = 0;

        for (Cartesien p : n) {
            sum_x += p.getX();
            sum_y += p.getY();
        }
        return Cartesien(sum_x / n.size(), sum_y / n.size());
    }
};

struct BarycentrePolaire {
    Polaire operator()(Nuage<Polaire> n) {
        Cartesien c;
        Polaire output;
        double sum_x = 0;
        double sum_y = 0;

        for (Polaire p : n) {
            p.convertir(c);
            sum_x += c.getX();
            sum_y += c.getY();
        }
        Cartesien(sum_x / n.size(), sum_y / n.size()).convertir(output);
        return output;
    }
};

#endif
