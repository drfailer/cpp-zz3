#ifndef CHAINE_HPP
#define CHAINE_HPP
#include "demangle.hpp"
#include <bits/utility.h>
#include <exception>
#include <sstream>
#include <string>

/******************************************************************************/
/*                                déclarations                                */
/******************************************************************************/

/* Déclaration des templates du plus général au plus spécifique. On doit avoir
 * ces déclarations pour permettre à `chaine(T... args)` d'appeler la fonction
 * `chaine(const std::tuple<Args...> &t)` qui est définie après pour pouvoir
 * afficher les tuples imbriqués. */
template<typename T> std::string chaine(T e);
template<typename ...T> std::string chaine(T... args);
template<typename ...Args> std::string chaine(const std::tuple<Args...> &t);
template<typename T, size_t... Is> std::string chaine(const T& t, std::index_sequence<Is...>);

/* les fonctions spécialisées */
std::string chaine(std::string s);
std::string chaine(double d);
std::string chaine(int i);


/******************************************************************************/
/*                              exception chaine                              */
/******************************************************************************/

struct ExceptionChaine: std::exception {
    /* ici, on a que le constructeur qui est template. Il prend l'objet sur
     * lequel on peut appliquer l'opérateur typeid(instance_obj). */
    template<typename T>
    ExceptionChaine(T value) : std::exception() {
        std::ostringstream oss;
        oss << "Conversion en chaine impossible pour '"
            << demangle(typeid(value).name()) << "'";
        msg = oss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }

    private:
        std::string msg;
};

/******************************************************************************/
/*                               generic chaine                               */
/******************************************************************************/

/* Méthode de base qui permet de renvoyer une exception pour les types inconnus
 * que l'on ne peut pas convertir en chaine.*/
template<typename T>
std::string chaine(T e) {
    throw ExceptionChaine(e);
}

/******************************************************************************/
/*                              chain variadique                              */
/******************************************************************************/

/* #define LAMBDA_VERSION */
/* #define STREAM_VERSION */
#if defined(LAMBDA_VERSION)
/*
 * Version où l'on utilise un lambda pour itérer sur les paramères. La syntaxe
 * est la suivante:
 *
 * ([&] { utilisation de args comme paramètre courant }(), ... )
 */
template<typename ...T>
std::string chaine(T... args) {
    std::ostringstream oss;

    /* on utilise un lambda pour itérer sur les arguements.
     * IMPORTAN: les {} sont bient avant les (). */
    ([&] {
     oss << chaine(args) << " ";
     }(), ...);
    return oss.str();
}
#elif defined(STREAM_VERSION)
/*
 * Version où l'on utilise un ostringstream pour construire la chaine.
 *
 * (stream << ... << (opération à réaliser sur args))
 */
template<typename ...T>
std::string chaine(T... args) {
    std::ostringstream oss;
    (oss << ... << (chaine(args) + " "));
    return oss.str();
}
#else
/*
 * Version où l'on utilise l'opérateur +
 *
 * ((opération à réaliser sur args) + ...)
 */
template<typename ...T>
std::string chaine(T... args) {
    return ((chaine(args) + " ") + ...);
}
#endif

/******************************************************************************/
/*                                   tuples                                   */
/******************************************************************************/

/* On prend un tuple en paramètre et on génère la séquence des indexes des
 * éléments du tuple. */
template<typename ...Args>
std::string chaine(const std::tuple<Args...> &t) {
    return chaine(t, std::make_index_sequence<sizeof...(Args)>());
}

/* On utilise une fold expression sur le tuple avec la séquence des indexes pour
 * pouvoir appeler la fonction `chaine(T... t)`. */
template<typename T, size_t... Is>
std::string chaine(const T& t, std::index_sequence<Is...>) {
    return chaine(std::get<Is>(t)...);
}

#endif
