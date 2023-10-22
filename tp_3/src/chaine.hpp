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

/* déclaration des templates du plus général au plus spécifique. */
template<typename T> std::string chaine(T e);
template<typename ...T> std::string chaine(T&&... args);
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

template<typename T>
std::string chaine(T e) {
    throw ExceptionChaine(e);
}

/******************************************************************************/
/*                              multi arguements                              */
/******************************************************************************/

template<typename ...T>
std::string chaine(T&&... args) {
    std::ostringstream oss;

    /* on utilise un lambda pour itérer sur les arguements.
     * IMPORTAN: les {} sont bient avant les (). */
    ([&] {
     oss << chaine(args) << " ";
     }(), ...);
    return oss.str();
}

/******************************************************************************/
/*                                   tuples                                   */
/******************************************************************************/

template<typename T, size_t... Is>
std::string chaine(const T& t, std::index_sequence<Is...>) {
    return chaine(std::get<Is>(t)...);
}

template<typename ...Args>
std::string chaine(const std::tuple<Args...> &t) {
    return chaine(t, std::make_index_sequence<sizeof...(Args)>());
}

#endif
