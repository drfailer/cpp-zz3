// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <complexe.hpp>

// Fonction principale //---------------------------------------------------------------------------
int main(void) {
 complexe_t::stats();

 std::cout << std::endl << "complexe_t c1(1,2);" << std::endl;
 complexe_t c1(1,2); // construction
 complexe_t::stats();

 std::cout << std::endl << "complexe_t c2(3,4);" << std::endl;
 complexe_t c2(3,4); // construction
 complexe_t::stats();

 std::cout << std::endl << "complexe_t c3(c1);" << std::endl;
 complexe_t c3(c1); // construction + copie
 complexe_t::stats();

 std::cout << std::endl << "complexe_t c4(std::move(c2));" << std::endl;
 complexe_t c4(std::move(c2)); // construction + déplacement
 complexe_t::stats();

 std::cout << std::endl << "c3=c1;" << std::endl;
 c3=c1; // copie
 complexe_t::stats();

 std::cout << std::endl << "c4=complexe_t(5,6);" << std::endl;
 c4=complexe_t(5,6); // construction + déplacement
 complexe_t::stats();

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------
