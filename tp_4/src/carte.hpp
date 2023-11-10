#ifndef CARTE_HPP
#define CARTE_HPP

class Carte
{
public:
    // friendship + forward declaration
    friend class UsineCarte;
    unsigned getValeur() const { return valeur; }
    ~Carte() {
        compteur--;
    }

    static int getCompteur() { return compteur; }

    // suppréssion du constructeur de copie / operateur d'affectation
    Carte(const Carte&) = delete;
    Carte& operator=(const Carte&) = delete;

private:
    Carte(int valeur): valeur(valeur) {
        compteur++;
    }
    unsigned valeur;
    inline static int compteur = 0;
};

#endif
