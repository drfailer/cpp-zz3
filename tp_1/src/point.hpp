#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
// #define CAST_METHOD

#ifndef CAST_METHOD
class Polaire;
class Cartesien;
#endif

class Point
{
public:
    /**************************************************************************/
    /* méthodes:                                                              */
    /**************************************************************************/
    virtual void afficher(std::ostream&) const = 0;

    #ifdef CAST_METHOD
    virtual void convertir(Point&) const = 0;
    #else
    virtual void convertir(Polaire&) const = 0;
    virtual void convertir(Cartesien&) const = 0;
    #endif

    /**************************************************************************/
    /* constructeurs & destructeurs:                                          */
    /**************************************************************************/

    // IMPORTANT: si la class est dérivable, il faut un destructeur virtuel.
    //            Dans ce cas il n'a pas nécessairement besoin d'être virtel pur
    //            mais j'aime bien que ce soit le cas dans mes classes abstraites
    //            (méthode virtuelle par défaut).
    // IMPORTANT: on doit toujours fornir l'implémentation d'un destructeur,
    //            même quand il est virtuel pur (cf: fichier cpp).
    //            Sur les compilateurs microsoft, on peut utiliser la syntaxe:
    //            virtual ~Point() = 0 {};
    //            MAIS CE N'EST PAS DANS LE STANDARD !
    virtual ~Point() = 0;
    /* virtual ~Point() {} // marche aussi */
};

std::ostream& operator<<(std::ostream& os, const Point& point);

#endif
