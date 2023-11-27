# TP3

## Template variadique

```cpp
template<typename ...T>
void fonc(T&... args) {
    // ...
}
```

## Meta-programmation

```cpp
template<int p>
struct Puissance {
    static const double valeur(double n) {
        return n * Puissance<p - 1>::valeur(n);
    }
};

// spécialisation du template pour le cas 0
template<>
struct Puissance<0> {
    static const double valeur(double n) {
        return 1;
    }
};
```
