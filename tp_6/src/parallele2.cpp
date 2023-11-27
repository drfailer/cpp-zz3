#include <cstdlib>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include "nombre.hpp"

/******************************************************************************/
/*                              global variables                              */
/******************************************************************************/

unsigned compteur = 0;
std::mutex mutex;

/******************************************************************************/
/*                               for sequentiel                               */
/******************************************************************************/

/**
 * Fonction demandée dans l'énnoncé. On utilise une macro pour éviter d'avoir à
 * écrire la lambda.
 */
#define for_seq(start, taille, code) for_sequentiel(start, taille, [&](size_t i) { code; })
void for_sequentiel(size_t start, size_t taille, std::function<void(size_t)> fonc) {
    for (size_t i = start; i < taille; ++i) {
        fonc(i);
    }
}

/******************************************************************************/
/*                               for parallele                                */
/******************************************************************************/

#define for_par(threads, start, taille, code) for_parallele<threads>(start, taille, [&](size_t i) { code; })
template<int N>
void for_parallele(size_t start, size_t taille, std::function<void(size_t)> fonc) {
    std::future<void> threads[N];

    for (size_t i = 0; i < N; i++) {
        threads[i] = std::async(std::launch::async, [=]() {
            for_seq(std::max(start, i * taille/N), (i + 1) * taille/N, fonc(i));
        });
    }
    /* Pas besoin d'utiliser `get` car la fonction parallélisée renvoie void. */
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

// #define SEQUENTIEL
// #define PARALLELE1
#define PARALLELE2
int main() {
    constexpr unsigned taille = 24;

    std::vector<Nombre> a(taille);
    std::vector<Nombre> b(taille);
    std::vector<Nombre> c(taille);
    std::vector<Nombre> d(taille);
    std::vector<Nombre> e(taille);
    std::vector<Nombre> f(taille);
    std::vector<Nombre> g(taille);

    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); a[i] = ++compteur; });
    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); b[i] = ++compteur; });
    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); c[i] = ++compteur; });
    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); d[i] = ++compteur; });
    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); e[i] = ++compteur; });
    for_par(4, 0, taille, { std::lock_guard<std::mutex> lock(mutex); f[i] = ++compteur; });

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "compteur = " << compteur << std::endl;

    /* test du calcul avec le for sequentiel et parallèle */

    #if defined(SEQUENTIEL)
    for_seq(0, taille, g[i] = a[i]*b[i] + c[i]/d[i] - e[i]*f[i]);
    #elif defined(PARALLELE1)
    for_par(6, 0, taille, g[i] = a[i]*b[i] + c[i]/d[i] - e[i]*f[i]);
    #elif defined(PARALLELE2)
    /* Pour la question 4, on ne peut pas réutiliser la fonction `for_parallele`
     * car on souhaite lancer tous les calculs en même temps. */

    // on peut aussi faire une jolie fonction mais ...
    #define setThread(thread, code)                                            \
        threads[thread] = std::async(std::launch::async, [&]() {               \
            for_seq(0, taille/2, code);                                        \
        });                                                                    \
        threads[thread + 1] = std::async(std::launch::async, [&]() {           \
            for_seq(taille/2, taille, code);                                   \
        });

    /* thread scope */ {
        std::future<void> threads[6];
        setThread(0, a[i] = a[i]*b[i]);
        setThread(2, c[i] = c[i]/d[i]);
        setThread(4, e[i] = e[i]*f[i]);
    }
    for_par(6, 0, taille, g[i] = a[i] + c[i] - e[i]);
    #endif

    std::cout << "g = " << g << std::endl;

    return 0;
}
