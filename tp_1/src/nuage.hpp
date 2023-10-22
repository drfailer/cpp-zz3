#ifndef NUAGE_HPP
#define NUAGE_HPP
#include "cartesien.hpp"
#include "polaire.hpp"
#include <point.hpp>
#include <vector>
#include <iterator>

class Nuage
{
public:
    /**************************************************************************/
    /* méthodes:                                                              */
    /**************************************************************************/
    void ajouter(Point&);
    int size() const { return points.size(); }

    /**************************************************************************/
    /* constructeurs & destructeurs:                                          */
    /**************************************************************************/
    Nuage() = default;
    ~Nuage() = default;

    /**************************************************************************/
    /* iterateur:                                                             */
    /**************************************************************************/

    /* Ici, le plus sage est de complètement recoder l'itérateur, mais on peut
     * aussi avoir la flemme et directement utilisé celui fournit par le
     * vecteur. Pour que le type Nuage::const_iterator soit utilisable dans les
     * test on utilise un using.
     *
     * NOTE: la classe for un espace de nom, c'est pour cela que dans les test
     * on doit utiliser Nuage::const_iterator et non directement const_iterator.
     * On peut aussi créer des espaces de noms avec le mot clé `namespace` (cf:
     * exercice 2).
     */
    using const_iterator = std::vector<Point*>::const_iterator;
    const_iterator begin() { return points.cbegin(); }
    const_iterator end() { return points.cend(); }

private:
    /* RAPPEL: Point est une classe abstraite donc on ne peut pas utiliser
     *         directement des objets, on doit utiliser des pointeurs.
     */
    std::vector<Point*> points;

};

/******************************************************************************/
/*                                 fonctions:                                 */
/******************************************************************************/

Cartesien barycentre(Nuage n);

/******************************************************************************/
/*                                 fonctors:                                  */
/******************************************************************************/

/* RAPPEL: pour créer un foncteur, il faut override `operator()` */

struct BarycentreCartesien {
    Cartesien operator()(Nuage n) const { return barycentre(n); }
};

struct BarycentrePolaire {
    Polaire operator()(Nuage n) const {
        Polaire p;
        Cartesien c = barycentre(n);
        c.convertir(p);
        return p;
    }
};

#endif
