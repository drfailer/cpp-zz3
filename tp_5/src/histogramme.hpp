#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include "classe.hpp"
#include "echantillon.hpp"
#include <algorithm>
#include <map>
#include <iostream>
#include <set>

class Histo
{
    public:
        std::vector<Classe> getClasses() const { return classes; }

    /* majouter ***************************************************************/
    void ajouter(Echantillon e) {
        for (Valeur v : e) {
            for (Classe& c : classes) {
                if (c.contains(v)) {
                    c.ajouter();
                    break;
                }
            }
        }
    }

    /* constructeurs & destructeur ********************************************/
    Histo(double borneInf, double borneSup, int nbClasses) {
        double step = (borneSup - borneInf) / nbClasses;

        for (double i = borneInf; i < borneSup; i+= step) {
            classes.push_back(Classe(i, i + step));
        }
    }

    Histo() = default;
    ~Histo() = default;

private:
    std::vector<Classe> classes;
};

struct Comp {
    bool operator()(const std::pair<Classe, Valeur>& lhs, const Classe& rhs) {
        return lhs.first < rhs;
    }
    bool operator()(const Classe& lhs, const std::pair<Classe, Valeur>& rhs) {
        return lhs < rhs.first;
    }
};

template<class Comparator = std::less<Classe>>
class Histogramme
{
public:
    std::set<Classe, Comparator> getClasses() const { return classes; }
    std::multimap<Classe, Valeur> getValeurs() const { return valeurs; }
    using const_iterator = std::multimap<Classe, Valeur>::const_iterator;
    std::pair<const_iterator, const_iterator> getValeurs(const Classe& c) const {
        return std::equal_range(valeurs.begin(), valeurs.end(), c, Comp());
    }

    /* majouter ***************************************************************/
    void ajouter(double v) {
        auto it = std::find_if(classes.begin(), classes.end(),
                [v](const Classe& c) { return c.contains(v); });
        if (it != classes.end()) {
            Classe updated = *it;
            classes.erase(it);
            updated.ajouter();
            classes.insert(updated);
            valeurs.insert(std::make_pair(*it, Valeur(v)));
        }
    }

    void ajouter(Echantillon e) {
        for (Valeur v : e) {
            auto it = std::find_if(classes.begin(), classes.end(),
                    [v](const Classe& c) { return c.contains(v); });
            if (it != classes.end()) {
                Classe updated = *it;
                classes.erase(it);
                updated.ajouter();
                classes.insert(updated);
                valeurs.insert(std::make_pair(*it, v));
            }
        }
    }

    /* constructeurs & destructeur ********************************************/
    Histogramme(double borneInf, double borneSup, int nbClasses) {
        double step = (borneSup - borneInf) / nbClasses;

        for (double i = borneInf; i < borneSup; i+= step) {
            classes.insert(Classe(i, i + step));
        }
    }

    template<typename T>
    Histogramme(const Histogramme<T>& other) {
        classes.clear();
        for (Classe c : other.getClasses()) {
            classes.insert(c);
        }
    }

    Histogramme() = default;
    ~Histogramme() = default;

private:
    std::set<Classe, Comparator> classes;
    std::multimap<Classe, Valeur> valeurs;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Histogramme<T> hist) {
    for (const Classe& c : hist.getClasses()) {
        auto interval = hist.getValeurs(c);

        os << "[" << c.getBorneInf() << ", " << c.getBorneSup() << "]:";
        for (auto it = interval.first; it != interval.second; ++it) {
            os << "(" << it->second.getEtudiant() << "," << it->second.getNote() << ") ";
        }
        os << std::endl;
    }

    return os;
}

#endif
