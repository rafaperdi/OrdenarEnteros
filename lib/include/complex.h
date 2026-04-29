#pragma once

#include <iostream>
#include <cmath>
#include <string>

class Complex {
public:
    // Constructores
    Complex() = default;
    Complex(double real, double imaginary = 0.0);
    
    // Getters
    double real() const noexcept;
    double imaginary() const noexcept;
    
    // Operaciones matemáticas
    double magnitude() const noexcept;  // Módulo |z|
    double phase() const noexcept;      // Ángulo (fase) en radianes
    Complex conjugate() const noexcept; // Conjugado
    
    // Operadores aritméticos
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Operadores de asignación
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    
    // Operadores unarios
    Complex operator+() const;
    Complex operator-() const;
    
    // Operadores de comparación
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    
    // Operador de impresión
    std::string toString() const;
    
private:
    double real_{0.0};
    double imaginary_{0.0};
    static constexpr double EPSILON = 1e-9;
};

// Operador de salida para std::cout
std::ostream& operator<<(std::ostream& os, const Complex& z);

// Operador de entrada para std::cin
std::istream& operator>>(std::istream& is, Complex& z);
