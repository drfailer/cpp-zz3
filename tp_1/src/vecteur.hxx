#ifndef VECTEUR_HPP
#define VECTEUR_HPP
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>
    #include <iostream>

namespace isima {
    template<typename T>
    class vecteur
    {
    public:
        /**********************************************************************/
        /* functions:                                                         */
        /**********************************************************************/

        /**
         * @brief  Append a value at the end of the vector.
         *         note: the memory is reallocated if needed so the worst case
         *         complexity is O(n) but most of the time it's O(1).
         * @param  value  Value to append.
         */
        void push_back(T value) {
            if (index_max >= mem_size) {
                T *tmp = mem;
                mem_size *= 2;
                mem = new T[mem_size];
                memcpy(mem, tmp, index_max * sizeof(T));
            }
            mem[index_max++] = value;
        }

        /**
         * @brief  Remove the last value of the vector.
         */
        void pop_back() {
            index_max--;
        }

        /**
         * @brief  Return the value at the end of the vector.
         *         note: if the vector is empty the result is undetermined.
         * @return  Las element of the vector.
         */
        T& back() { return mem[index_max - 1]; }

        /**
         * @brief  Return the value at the end of the constant vector.
         *         note: if the vector is empty the result is undetermined.
         * @return  Las element of the vector.
         */
        const T& back() const { return mem[index_max - 1]; }

        /**
         * @brief  Add a value to the front of the vector.
         *         This methode is not optmized so the complexity is always
         *         O(n).
         * @param  value  Value to put on the front of the vector.
         */
        void push_front(int value) {
            if (index_max >= mem_size) {
                T *tmp = mem;
                mem_size *= 2;
                mem = new T[mem_size];
                memcpy(mem + 1, tmp, index_max * sizeof(T));
            } else {
                for (int i = index_max; i > 0; --i) {
                    mem[i] = mem[i - 1];
                }
            }
            index_max++;
            mem[0] = value;
        }

        /**
         * @brief  Remove the first value of the vector.
         *         This methode is not optmized so the complexity is always
         *         O(n).
         */
        void pop_front() {
            for (int i = 0; i < index_max - 1; ++i) {
                mem[i] = mem[i + 1];
            }
        }

        /**
         * @brief  Return the first value of the vector.
         *         note: if the vector is empty, the result is undetermined.
         *
         * @return  First value of the vector.
         */
        T& front() { return mem[0]; }

        /**
         * @brief  Return the first value of the constant vector.
         *         note: if the vector is empty, the result is undetermined.
         *
         * @return  First value of the vector.
         */
        const T& front() const { return mem[0]; }

        /**
         * @brief  Return the number of elements in the vector.
         * @return  Number of elements in the vector.
         */
        long size() const { return index_max; }

        /**********************************************************************/
        /* operators:                                                         */
        /**********************************************************************/

        /**
         * @brief  Acces to the element of the vector.
         *         note: if the index is out of bound the result is
         *         undetermined.
         * @param  index  Index to access.
         * @return  Value at `index`.
         */
        T& operator[](int index) { return mem[index]; }

        /**
         * @brief  Acces to the element of the constant vector.
         *         note: if the index is out of bound the result is
         *         undetermined.
         * @param  index  Index to access.
         * @return  Value at `index`.
         */
        const T& operator[](int index) const { return mem[index]; }

        /**
         * @brief  Concatenate 2 vectors.
         * @param  lhs  First vector.
         * @param  rhs  Second vector.
         * @return  Result of the concatenation
         */
        template<typename U>
        friend vecteur<U> operator+(const vecteur<U>& lhs, const vecteur<U>& rhs);

        /**********************************************************************/
        /* iterator:                                                          */
        /**********************************************************************/

        class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            iterator(T *init): ptr(init) {}
            ~iterator() = default;

            bool operator==(const iterator& other) const {
                return other.ptr == ptr;
            }

            bool operator!=(const iterator& other) const {
                return other.ptr != ptr;
            }

            iterator operator++() {
                ++ptr;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp(ptr);
                ++(*this);
                return tmp;
            }

            iterator operator--() {
                --ptr;
                return *this;
            }

            iterator operator--(int) {
                iterator tmp(ptr);
                --(*this);
                return tmp;
            }

            T& operator*() {
                return *iterator::ptr;
            }

            T* operator->() {
                return iterator::ptr;
            }

            const T& operator*() const {
                return *iterator::ptr;
            }

            const T* operator->() const {
                return iterator::ptr;
            }

            difference_type operator-(const iterator& other) const {
                return ptr - other.ptr;
            }

            iterator operator-(int i) const {
                return iterator(ptr - i);
            }

            iterator operator+(int i) const {
                return iterator(ptr + i);
            }

            iterator operator*(int i) const {
                return iterator(ptr * i);
            }

            bool operator<(const iterator& other) const {
                return ptr < other.ptr;
            }

        private:
            T *ptr;
        };

        iterator begin() { return iterator(mem); }
        iterator end() { return iterator(mem + index_max); }
        iterator begin() const { return iterator(mem); }
        iterator end() const { return iterator(mem + index_max); }
        iterator cbegin() const { return iterator(mem); }
        iterator cend() const { return iterator(mem + index_max); }

        /**********************************************************************/
        /* constructors:                                                      */
        /**********************************************************************/

        /**
         * @brief  Construct a vector with memory size.
         * @param  mem_size  Memory size of the vector (default 100).
         */
        vecteur(long mem_size = 100): mem_size(mem_size) {
            mem = new T[mem_size];
        }

        /**
         * @brief  Construct a vector with initializer list.
         * @param  init  Initializer list constaining the values to put in the
         *               vector.
         */
        vecteur(std::initializer_list<T> init): vecteur(2 * init.size()) {
            for (T e : init) {
                mem[index_max++] = e;
            }
        }

        /**
         * @brief  Copy constructor
         * @param  other  Other vector to copy.
         */
        vecteur(const vecteur<T>& other): index_max(other.index_max), mem_size(other.mem_size) {
            mem = new T[other.mem_size];
            memcpy(mem, other.mem, other.index_max * sizeof(T));
        }

        ~vecteur() {
            delete[] mem;
        }

    private:
        T *mem;
        long index_max = 0;
        long mem_size;
    };

    /**
     * @brief  Concatenate 2 vectors.
     * @param  lhs  First vector.
     * @param  rhs  Second vector.
     * @return  Result of the concatenation
     */
    template<typename T>
    vecteur<T> operator+(const vecteur<T>& lhs, const vecteur<T>& rhs) {
        vecteur<T> result(2 * (lhs.size() + rhs.size()));

        memcpy(result.mem, lhs.mem, lhs.size() * sizeof(T));
        memcpy(result.mem + lhs.size(), rhs.mem, rhs.size() * sizeof(T));
        result.index_max = lhs.size() + rhs.size();
        return result;
    }

    /**
     * @brief  Perform a scalar product on 2 vectors.
     * @param  lhs  First vector.
     * @param  rhs  Second vector.
     * @return  Result of the scalar product
     */
    template<typename T>
    T operator*(const vecteur<T>& lhs, const vecteur<T>& rhs) {
        T result{0};

        if (lhs.size() != rhs.size()) {
            throw std::logic_error("Error: illegal operation on vectors with different sizes.");
        }

        for (int i = 0; i < lhs.size(); ++i) {
            result += lhs[i] * rhs[i];
        }

        return result;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const vecteur<T>& vec) {
        os << "[";
        for (const T e : vec) {
            os << " " << e;
        }
        os << " ]";
        return os;
    }
}

#endif
