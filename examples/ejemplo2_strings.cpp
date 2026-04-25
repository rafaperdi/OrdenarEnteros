#include "array.h"
#include "sorting.h"
#include <iostream>
#include <string>

// Ejemplo 2: Ordenar strings y usar comparadores descendentes
int main() {
    std::cout << "Ejemplo 2: Ordenar strings y descendente\n" << std::endl;
    
    Array<std::string> ciudades{"Madrid", "Barcelona", "Valencia", "Sevilla", "Zaragoza"};
    
    std::cout << "Original: ";
    ciudades.print();
    
    // Ordenar ascendente
    ordenar(ciudades);
    std::cout << "Ascendente: ";
    ciudades.print();
    
    // Ordenar descendente
    struct ComparadorDesc {
        bool operator()(const std::string& a, const std::string& b) const {
            return a > b;
        }
    };
    
    ordenar(ciudades, ComparadorDesc());
    std::cout << "Descendente: ";
    ciudades.print();
    
    return 0;
}
