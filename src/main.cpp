#include "Array.h"
#include "int_sort.h"
#include <iostream>
#include <string>

// Clase customizada de ejemplo
class Persona {
public:
    std::string nombre;
    int edad;

    Persona() : nombre(""), edad(0) {}
    Persona(const std::string& n, int e) : nombre(n), edad(e) {}

    // Operador de comparación para ordenar por edad
    bool operator<(const Persona& otro) const {
        return edad < otro.edad;
    }

    // Operador de salida para impresión
    friend std::ostream& operator<<(std::ostream& os, const Persona& p) {
        return os << p.nombre << "(" << p.edad << ")";
    }
};

// Comparador customizado para ordenar Personas por nombre
struct ComparadorPorNombre {
    bool operator()(const Persona& a, const Persona& b) const {
        return a.nombre < b.nombre;
    }
};

// Comparador para orden descendente
template <typename T>
struct ComparadorDescendente {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

int main() {
    std::cout << "=== PRUEBAS DE ORDENAMIENTO GENÉRICO ===" << std::endl << std::endl;

    // ========== PRUEBA 1: Integers ==========
    std::cout << "--- Prueba 1: Ordenamiento de Integers ---" << std::endl;
    Array<int> enteros{8, 3, 5, 1, 9, 2, 7, 4};
    std::cout << "Antes: ";
    enteros.print();
    ordenar(enteros);
    std::cout << "Después (Selection Sort Ascendente): ";
    enteros.print();
    std::cout << std::endl;

    // ========== PRUEBA 2: Doubles ==========
    std::cout << "--- Prueba 2: Ordenamiento de Doubles ---" << std::endl;
    Array<double> decimales{3.14, 2.71, 1.41, 4.44, 1.73};
    std::cout << "Antes: ";
    decimales.print();
    ordenar(decimales);
    std::cout << "Después (Selection Sort Ascendente): ";
    decimales.print();
    std::cout << std::endl;

    // ========== PRUEBA 3: Strings ==========
    std::cout << "--- Prueba 3: Ordenamiento de Strings ---" << std::endl;
    Array<std::string> palabras{"zebra", "apple", "mango", "banana", "cherry"};
    std::cout << "Antes: ";
    palabras.print();
    ordenar(palabras);
    std::cout << "Después (Selection Sort Alfabético): ";
    palabras.print();
    std::cout << std::endl;

    // ========== PRUEBA 4: Objetos Customizados (Personas por edad) ==========
    std::cout << "--- Prueba 4: Ordenamiento de Objetos (Personas por edad) ---" << std::endl;
    Array<Persona> personas{
        Persona("Alice", 30),
        Persona("Bob", 25),
        Persona("Charlie", 35),
        Persona("Diana", 28),
        Persona("Eve", 22)
    };
    std::cout << "Antes: ";
    personas.print();
    ordenar(personas);
    std::cout << "Después (Por edad): ";
    personas.print();
    std::cout << std::endl;

    // ========== PRUEBA 5: Objetos Customizados (Personas por nombre) ==========
    std::cout << "--- Prueba 5: Ordenamiento de Objetos (Personas por nombre) ---" << std::endl;
    Array<Persona> personas2{
        Persona("Zoe", 30),
        Persona("Bob", 25),
        Persona("Alice", 35),
        Persona("Diana", 28),
        Persona("Eve", 22)
    };
    std::cout << "Antes: ";
    personas2.print();
    ordenar(personas2, ComparadorPorNombre());
    std::cout << "Después (Por nombre): ";
    personas2.print();
    std::cout << std::endl;

    // ========== PRUEBA 6: Orden Descendente ==========
    std::cout << "--- Prueba 6: Ordenamiento Descendente de Integers ---" << std::endl;
    Array<int> enteros2{8, 3, 5, 1, 9, 2, 7, 4};
    std::cout << "Antes: ";
    enteros2.print();
    ordenar(enteros2, ComparadorDescendente<int>());
    std::cout << "Después (Descendente): ";
    enteros2.print();
    std::cout << std::endl;

    // ========== PRUEBA 7: Orden Descendente Strings ==========
    std::cout << "--- Prueba 7: Ordenamiento Descendente de Strings ---" << std::endl;
    Array<std::string> palabras2{"zebra", "apple", "mango", "banana", "cherry"};
    std::cout << "Antes: ";
    palabras2.print();
    ordenar(palabras2, ComparadorDescendente<std::string>());
    std::cout << "Después (Descendente): ";
    palabras2.print();
    std::cout << std::endl;

    // ========== PRUEBA 8: Quicksort con Integers ==========
    std::cout << "--- Prueba 8: QuickSort de Integers ---" << std::endl;
    Array<int> enteros3{8, 3, 5, 1, 9, 2, 7, 4};
    std::cout << "Antes: ";
    enteros3.print();
    quickSort(enteros3);
    std::cout << "Después (QuickSort): ";
    enteros3.print();
    std::cout << std::endl;

    std::cout << "=== FIN DE LAS PRUEBAS ===" << std::endl;

    return 0;
}

