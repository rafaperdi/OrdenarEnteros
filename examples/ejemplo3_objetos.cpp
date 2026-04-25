#include "array.h"
#include "sorting.h"
#include <iostream>
#include <string>

// Ejemplo 3: Ordenar objetos customizados
struct Producto {
    std::string nombre;
    double precio;
    
    Producto() : nombre(""), precio(0.0) {}
    Producto(const std::string& n, double p) : nombre(n), precio(p) {}
    
    // Comparar por precio (ascendente)
    bool operator<(const Producto& otro) const {
        return precio < otro.precio;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Producto& p) {
        return os << p.nombre << "($" << p.precio << ")";
    }
};

// Comparador por nombre (alfabético)
struct ComparadorPorNombre {
    bool operator()(const Producto& a, const Producto& b) const {
        return a.nombre < b.nombre;
    }
};

int main() {
    std::cout << "Ejemplo 3: Ordenar objetos customizados\n" << std::endl;
    
    Array<Producto> productos{
        Producto("Laptop", 999.99),
        Producto("Mouse", 29.99),
        Producto("Teclado", 79.99),
        Producto("Monitor", 299.99),
        Producto("Webcam", 59.99)
    };
    
    std::cout << "Original: ";
    productos.print();
    
    // Ordenar por precio
    ordenar(productos);
    std::cout << "Por precio: ";
    productos.print();
    
    // Ordenar por nombre
    ordenar(productos, ComparadorPorNombre());
    std::cout << "Por nombre: ";
    productos.print();
    
    return 0;
}
