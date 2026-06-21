#include "complex.h"
#include <sstream>
#include <iomanip>

// Constructor parametrizado
Complex::Complex(double real, double imaginary)
    : real_(real), imaginary_(imaginary) {}

// Getters
double Complex::real() const noexcept {
    return real_;
}

double Complex::imaginary() const noexcept {
    return imaginary_;
}

// Obtener el módulo (magnitud) del número complejo
double Complex::magnitude() const noexcept {
    return std::hypot(real_, imaginary_);
}

// Obtener la fase (ángulo) en radianes
double Complex::phase() const noexcept {
    return std::atan2(imaginary_, real_);
}

// Obtener el conjugado
Complex Complex::conjugate() const noexcept {
    return Complex(real_, -imaginary_);
}

// Suma
Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imaginary_ + other.imaginary_);
}

// Resta
Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imaginary_ - other.imaginary_);
}

// Multiplicación: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
Complex Complex::operator*(const Complex& other) const {
    double real_part = real_ * other.real_ - imaginary_ * other.imaginary_;
    double imag_part = real_ * other.imaginary_ + imaginary_ * other.real_;
    return Complex(real_part, imag_part);
}

// División: (a + bi) / (c + di) = ((ac + bd) + (bc - ad)i) / (c² + d²)
Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imaginary_ * other.imaginary_;
    
    if (denominator == 0.0) {
        throw std::invalid_argument("División por cero (número complejo con magnitud cero)");
    }
    
    double real_part = (real_ * other.real_ + imaginary_ * other.imaginary_) / denominator;
    double imag_part = (imaginary_ * other.real_ - real_ * other.imaginary_) / denominator;
    return Complex(real_part, imag_part);
}

// Operadores de asignación compuesta
Complex& Complex::operator+=(const Complex& other) {
    real_ += other.real_;
    imaginary_ += other.imaginary_;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real_ -= other.real_;
    imaginary_ -= other.imaginary_;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    *this = *this * other;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    *this = *this / other;
    return *this;
}

// Operadores unarios
Complex Complex::operator+() const {
    return Complex(real_, imaginary_);
}

Complex Complex::operator-() const {
    return Complex(-real_, -imaginary_);
}

// Comparación
bool Complex::operator==(const Complex& other) const {
    return (std::abs(real_ - other.real_) < EPSILON) &&
           (std::abs(imaginary_ - other.imaginary_) < EPSILON);
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Convertir a string
std::string Complex::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    
    if (imaginary_ == 0.0) {
        oss << real_;
    } else if (real_ == 0.0) {
        oss << imaginary_ << "i";
    } else {
        oss << real_;
        if (imaginary_ > 0) {
            oss << " + " << imaginary_ << "i";
        } else {
            oss << " - " << std::abs(imaginary_) << "i";
        }
    }
    
    return oss.str();
}

// Operador de salida
std::ostream& operator<<(std::ostream& os, const Complex& z) {
    os << z.toString();
    return os;
}

// Operador de entrada
std::istream& operator>>(std::istream& is, Complex& z) {
    double real, imaginary;
    is >> real >> imaginary;
    z = Complex(real, imaginary);
    return is;
}
