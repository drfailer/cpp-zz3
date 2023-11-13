#ifndef VALEUR_HPP
#define VALEUR_HPP
#include <string>

class Valeur
{
    public:
        void setEtudiant(std::string etudiant) { this->etudiant = etudiant; }
        std::string getEtudiant() const { return etudiant; }
        void setNombre(double nombre) { this->nombre = nombre; }
        void setNote(double nombre) { this->nombre = nombre; }
        double getNombre() const { return nombre; }
        double getNote() const { return nombre; }
        Valeur(double nombre, std::string etudiant): nombre(nombre), etudiant(etudiant) {}
        Valeur(double nombre): Valeur(nombre, "inconnu") {}
        Valeur() = default;
        ~Valeur() = default;

private:
    double nombre = 0;
    std::string etudiant = "inconnu";
};

inline bool operator<(const Valeur& v1, const Valeur& v2) {
    return v1.getNombre() < v2.getNombre();
}

#endif
