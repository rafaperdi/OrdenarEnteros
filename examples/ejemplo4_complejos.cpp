#include <iostream>
#include "../lib/include/complex.h"

int main() {
    std::cout << "=== Ejemplo de Números Complejos ===" << std::endl << std::endl;
    
    // Crear algunos números complejos
    Complex z1(3.0, 4.0);      // 3 + 4i
    Complex z2(1.0, 2.0);      // 1 + 2i
    Complex z3(2.0);            // 2 + 0i
    Complex z4(0.0, 5.0);       // 0 + 5i
    
    std::cout << "Números complejos creados:" << std::endl;
    std::cout << "z1 = " << z1 << std::endl;
    std::cout << "z2 = " << z2 << std::endl;
    std::cout << "z3 = " << z3 << std::endl;
    std::cout << "z4 = " << z4 << std::endl;
    std::cout << std::endl;
    
    // Getters
    std::cout << "Partes del número complejo z1:" << std::endl;
    std::cout << "Parte real: " << z1.real() << std::endl;
    std::cout << "Parte imaginaria: " << z1.imaginary() << std::endl;
    std::cout << std::endl;
    
    // Propiedades matemáticas
    std::cout << "Propiedades matemáticas de z1:" << std::endl;
    std::cout << "Magnitud (módulo): " << z1.magnitude() << std::endl;
    std::cout << "Fase (ángulo): " << z1.phase() << " radianes" << std::endl;
    std::cout << "Conjugado: " << z1.conjugate() << std::endl;
    std::cout << std::endl;
    
    // Operaciones aritméticas
    std::cout << "Operaciones aritméticas:" << std::endl;
    std::cout << "z1 + z2 = " << (z1 + z2) << std::endl;
    std::cout << "z1 - z2 = " << (z1 - z2) << std::endl;
    std::cout << "z1 * z2 = " << (z1 * z2) << std::endl;
    try {
        std::cout << "z1 / z2 = " << (z1 / z2) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en división: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    
    // Operadores unarios
    std::cout << "Operadores unarios:" << std::endl;
    std::cout << "+z1 = " << (+z1) << std::endl;
    std::cout << "-z1 = " << (-z1) << std::endl;
    std::cout << std::endl;
    
    // Operadores de asignación
    Complex temp = z1;
    temp += z2;
    std::cout << "z1 += z2 = " << temp << std::endl;
    
    temp = z1;
    temp -= z2;
    std::cout << "z1 -= z2 = " << temp << std::endl;
    
    temp = z1;
    temp *= z2;
    std::cout << "z1 *= z2 = " << temp << std::endl;
    std::cout << std::endl;
    
    // Comparaciones
    std::cout << "Comparaciones:" << std::endl;
    std::cout << "z1 == z1: " << (z1 == z1 ? "verdadero" : "falso") << std::endl;
    std::cout << "z1 == z2: " << (z1 == z2 ? "verdadero" : "falso") << std::endl;
    std::cout << "z1 != z2: " << (z1 != z2 ? "verdadero" : "falso") << std::endl;
    std::cout << std::endl;
    
    return 0;
}
