#include <cstdlib>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include "nombre.hpp"
#define thread_sleep(n) { using namespace std::chrono_literals; std::this_thread::sleep_for(n); }

/******************************************************************************/
/*                              global variables                              */
/******************************************************************************/

unsigned compteur = 0;
std::mutex mutex;

/******************************************************************************/
/*                               exemples cours                               */
/******************************************************************************/

void fonc1() {
    std::cout << "plouf" << std::endl;
    thread_sleep(1s);
}

void fonc2(int n) {
    std::cout << "[" << n << "]" << std::endl;
    thread_sleep(1s);
}

void fonc3(int n) {
    mutex.lock();
    std::cout << "[" << n << "]" << std::endl;
    mutex.unlock();
    thread_sleep(1s);
}

/******************************************************************************/
/*                                   tests                                    */
/******************************************************************************/

void test1() {
    std::thread t(fonc1);
    t.join();
}

void test2() {
    std::thread t[4];

    for (int i = 0; i < 4; ++i) { t[i] = std::thread(fonc2, i); }
    for (int i = 0; i < 4; ++i) { t[i].join(); }
}

void test3() {
    std::thread t[4];

    for (int i = 0; i < 4; ++i) { t[i] = std::thread(fonc3, i); }
    for (int i = 0; i < 4; ++i) { t[i].join(); }
}

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
    std::thread threads[N];

    for (size_t i = 0; i < N; i++) {
        threads[i] = std::thread([=]() {
            for_seq(std::max(start, i * taille/N), (i + 1) * taille/N, fonc(i));
        });
    }

    for (size_t i = 0; i < N; i++) {
        threads[i].join();
    }
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

int main() {
    constexpr unsigned taille = 24;

    std::vector<Nombre> a(taille);
    std::vector<Nombre> b(taille);
    std::vector<Nombre> c(taille);

    /* sans protection du compteur */
    /* for_par(4, 0, taille, a[i] = ++compteur); */
    /* for_par(4, 0, taille, b[i] = ++compteur); */

    /* WARNING:
     *
     * Je suppose que ce qui est attendu est quelque chose de similaire à ce
     * qui est fait ci-dessous. Si ça ne marche pas c'est tout à fait normal et
     * en l'état je ne voix pas comment faire pour utiliser la fonction
     * `for_parallele` pour générer les tableau avec le compteur. Le problème de
     * l'utilisation du compteur global ici est qu'il force à faire les choses
     * de façon séquentielle, dans le cas contraire, les tableaux n'ont pas
     * forcement les bonnes valeurs.
     *
     * À noter qu'il est possible d'ajouter des mutex dans la fontion
     * `for_parallele` pour habilement la transformer en un `for_sequentiel`
     * inutilement complexe mais je doute que cela soit la solution.
     *
     * NOTE: il y a une solution possible (sans avoir besoin de mutex et de
     * compteur global) présentée dans le fichier `parallele2.cpp`.
     */

    /* utilisation directe du mutex (déconseillée) */
    for_par(4, 0, taille, {
        mutex.lock();
        a[i] = ++compteur;
        mutex.unlock();
    });
    /* utilisation de lock_guard */
    for_par(4, 0, taille, {
            std::lock_guard<std::mutex> lock(mutex);
            b[i] = ++compteur;
        }
    );

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "compteur = " << compteur << std::endl;

    for_par(4, 0, taille, c[i] = a[i]*b[i]);

    std::cout << "c = " << c << std::endl;

    return 0;
}
