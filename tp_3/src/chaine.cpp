#include "chaine.hpp"
#include <sstream>
#include <cstdio>
#include <string>

std::string chaine(std::string s) {
    return s;
}

std::string chaine(double d) {
    return std::to_string(d);
}

std::string chaine(int i) {
    std::ostringstream oss;
    oss << i;
    return oss.str();
}
