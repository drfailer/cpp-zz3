#include "nuage.hpp"

void Nuage::ajouter(Point& p) {
    points.push_back(&p);
}

Cartesien barycentre(Nuage n) {
    Cartesien current;
    double total_x = 0;
    double total_y = 0;

    /* n est itérable donc on peut utiliser cette synctaxe, le compilateur
     * génère le code qui fait appel aux méthodes begin() et end().
     */
    for (Point *p : n) {
        p->convertir(current);
        total_x += current.getX();
        total_y += current.getY();
    }
    return Cartesien(total_x / n.size(), total_y / n.size());
}
