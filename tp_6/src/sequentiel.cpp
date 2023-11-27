// Entetes //---------------------------------------------------------------------------------------
#include <functional>
#include <nombre.hpp>

// Variables globales //----------------------------------------------------------------------------
unsigned compteur = 0;

// For sequentiel //--------------------------------------------------------------------------------
#define for_seq(start, taille, code) for_sequentiel(start, taille, [&](size_t i) { code; })
void for_sequentiel(size_t start, size_t taille, std::function<void(size_t)> fonc) {
    for (size_t i = start; i < taille; ++i) {
        fonc(i);
    }
}

// Fonction principale //---------------------------------------------------------------------------
int main() {
 const unsigned taille = 24;

 std::vector<Nombre> a(taille);
 std::vector<Nombre> b(taille);
 std::vector<Nombre> c(taille);

 for_seq(0, taille, a[i] = ++compteur);
 for_seq(0, taille, b[i] = ++compteur);

 std::cout << "a = " << a << std::endl;
 std::cout << "b = " << b << std::endl;
 std::cout << "compteur = " << compteur << std::endl;

 for_seq(0, taille, c[i] = a[i]*b[i]);

 std::cout << "c = " << c << std::endl;

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------
