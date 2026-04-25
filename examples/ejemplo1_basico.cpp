#include "array.h"
#include "sorting.h"
#include <iostream>

// Ejemplo 1: Ordenar números enteros
int main() {
    std::cout << "Ejemplo 1: Ordenamiento básico de enteros\n" << std::endl;
    
    Array<int> numeros{42, 17, 93, 5, 38, 11, 64, 28};
    
    std::cout << "Original: ";
    numeros.print();
    
    ordenar(numeros);
    
    std::cout << "Ordenado: ";
    numeros.print();
    
    return 0;
}
