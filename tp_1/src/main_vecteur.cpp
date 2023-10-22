#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "vecteur.hxx"

int main() {
    isima::vecteur<int> v1 = {1, 2, 3};
    isima::vecteur<int> v2 = {4, 2, 1};

    std::cout << v1 << std::endl;
    std::cout << (v1 + v2) << std::endl;
    std::cout << (v1 * v2) << std::endl;

    std::sort(v2.begin(), v2.end());
    std::cout << v2 << std::endl;

    for (int i = 0; i < 500; ++i) {
        v1.push_back(i);
    }
    std::cout << v1.size() << std::endl;
    std::cout << v1 << std::endl;

    return EXIT_SUCCESS;
}
