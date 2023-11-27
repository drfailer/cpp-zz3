# TP1

## Les foncteurs

Pour créer un foncteur, on fait une structure et on implémente `operator()`.

```cpp
struct Double {
    int operator()(int n) {
        return 2*n;
    }
}
```

## Les itérateurs

### Utilisation d'un itérateur existant

```cpp
template<typename T>
class MyClass {
    public:
        using iterator = typename std::vector<T>::iterator;
        iterator begin() { return vec.begin(); }
        iterator end() { return vec.end(); }

    private:
        std::vector<T> vec;
};
```

## Création d'un itérateur

**IMPORTANT**: ne surtout pas oublier les tags (`value_type`, ...), ils sont
importants pour `algorithm`.

```cpp
template<typename T>
struct my_class {
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator(T *init): ptr(init) {}
        ~iterator() = default;

        bool operator==(const iterator& other) const { return other.ptr == ptr; }
        bool operator!=(const iterator& other) const { return other.ptr != ptr; }

        iterator operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp(ptr); ++(*this); return tmp; }
        iterator operator--() { --ptr; return *this; }
        iterator operator--(int) { iterator tmp(ptr); --(*this); return tmp; }

        T& operator*() { return *iterator::ptr; }
        T* operator->() { return iterator::ptr; }
        const T& operator*() const { return *iterator::ptr; }
        const T* operator->() const { return iterator::ptr; }

        difference_type operator-(const iterator& other) const { return ptr - other.ptr; }
        iterator operator-(int i) const { return iterator(ptr - i); }
        iterator operator+(int i) const { return iterator(ptr + i); }
        iterator operator*(int i) const { return iterator(ptr * i); }
        bool operator<(const iterator& other) const { return ptr < other.ptr; }

    private:
        T *ptr;
    };

    iterator begin() { return iterator(mem); }
    iterator end() { return iterator(mem + index_max); }
    iterator begin() const { return iterator(mem); }
    iterator end() const { return iterator(mem + index_max); }
};
```
