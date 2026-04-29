#include <gtest/gtest.h>
#include "../lib/include/complex.h"
#include <cmath>

// ============================================================================
// Pruebas de Constructores
// ============================================================================

TEST(ComplexTest, DefaultConstructor) {
    Complex z;
    EXPECT_EQ(z.real(), 0.0);
    EXPECT_EQ(z.imaginary(), 0.0);
}

TEST(ComplexTest, ParametrizedConstructor) {
    Complex z(3.0, 4.0);
    EXPECT_EQ(z.real(), 3.0);
    EXPECT_EQ(z.imaginary(), 4.0);
}

TEST(ComplexTest, ConstructorWithOnlyReal) {
    Complex z(5.0);
    EXPECT_EQ(z.real(), 5.0);
    EXPECT_EQ(z.imaginary(), 0.0);
}

// ============================================================================
// Pruebas de Getters
// ============================================================================

TEST(ComplexTest, RealPart) {
    Complex z(7.5, 2.3);
    EXPECT_EQ(z.real(), 7.5);
}

TEST(ComplexTest, ImaginaryPart) {
    Complex z(7.5, 2.3);
    EXPECT_EQ(z.imaginary(), 2.3);
}

// ============================================================================
// Pruebas de Operaciones Matemáticas
// ============================================================================

TEST(ComplexTest, Magnitude) {
    // Triángulo pitagórico: 3-4-5
    Complex z(3.0, 4.0);
    EXPECT_DOUBLE_EQ(z.magnitude(), 5.0);
}

TEST(ComplexTest, MagnitudeOfZero) {
    Complex z(0.0, 0.0);
    EXPECT_DOUBLE_EQ(z.magnitude(), 0.0);
}

TEST(ComplexTest, MagnitudeRealOnly) {
    Complex z(5.0, 0.0);
    EXPECT_DOUBLE_EQ(z.magnitude(), 5.0);
}

TEST(ComplexTest, MagnitudeImaginaryOnly) {
    Complex z(0.0, 3.0);
    EXPECT_DOUBLE_EQ(z.magnitude(), 3.0);
}

TEST(ComplexTest, Phase) {
    // Fase de 3 + 4i debería estar en el primer cuadrante
    Complex z(3.0, 4.0);
    double expectedPhase = std::atan2(4.0, 3.0);
    EXPECT_DOUBLE_EQ(z.phase(), expectedPhase);
}

TEST(ComplexTest, Conjugate) {
    Complex z(3.0, 4.0);
    Complex conj = z.conjugate();
    EXPECT_EQ(conj.real(), 3.0);
    EXPECT_EQ(conj.imaginary(), -4.0);
}

TEST(ComplexTest, ConjugateOfConjugate) {
    Complex z(3.0, 4.0);
    Complex conj = z.conjugate().conjugate();
    EXPECT_EQ(conj.real(), z.real());
    EXPECT_EQ(conj.imaginary(), z.imaginary());
}

// ============================================================================
// Pruebas de Suma
// ============================================================================

TEST(ComplexTest, Addition) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    Complex result = z1 + z2;
    EXPECT_EQ(result.real(), 4.0);
    EXPECT_EQ(result.imaginary(), 6.0);
}

TEST(ComplexTest, AdditionWithZero) {
    Complex z(3.0, 4.0);
    Complex zero(0.0, 0.0);
    Complex result = z + zero;
    EXPECT_EQ(result.real(), z.real());
    EXPECT_EQ(result.imaginary(), z.imaginary());
}

TEST(ComplexTest, AdditionCommutative) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    Complex result1 = z1 + z2;
    Complex result2 = z2 + z1;
    EXPECT_EQ(result1.real(), result2.real());
    EXPECT_EQ(result1.imaginary(), result2.imaginary());
}

// ============================================================================
// Pruebas de Resta
// ============================================================================

TEST(ComplexTest, Subtraction) {
    Complex z1(5.0, 8.0);
    Complex z2(2.0, 3.0);
    Complex result = z1 - z2;
    EXPECT_EQ(result.real(), 3.0);
    EXPECT_EQ(result.imaginary(), 5.0);
}

TEST(ComplexTest, SubtractionWithZero) {
    Complex z(3.0, 4.0);
    Complex zero(0.0, 0.0);
    Complex result = z - zero;
    EXPECT_EQ(result.real(), z.real());
    EXPECT_EQ(result.imaginary(), z.imaginary());
}

TEST(ComplexTest, SubtractionSelf) {
    Complex z(5.0, 3.0);
    Complex result = z - z;
    EXPECT_EQ(result.real(), 0.0);
    EXPECT_EQ(result.imaginary(), 0.0);
}

// ============================================================================
// Pruebas de Multiplicación
// ============================================================================

TEST(ComplexTest, Multiplication) {
    // (3 + 4i) * (1 + 2i) = 3 + 6i + 4i + 8i² = 3 + 10i - 8 = -5 + 10i
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    Complex result = z1 * z2;
    EXPECT_EQ(result.real(), -5.0);
    EXPECT_EQ(result.imaginary(), 10.0);
}

TEST(ComplexTest, MultiplicationByZero) {
    Complex z(3.0, 4.0);
    Complex zero(0.0, 0.0);
    Complex result = z * zero;
    EXPECT_EQ(result.real(), 0.0);
    EXPECT_EQ(result.imaginary(), 0.0);
}

TEST(ComplexTest, MultiplicationByOne) {
    Complex z(3.0, 4.0);
    Complex one(1.0, 0.0);
    Complex result = z * one;
    EXPECT_EQ(result.real(), z.real());
    EXPECT_EQ(result.imaginary(), z.imaginary());
}

TEST(ComplexTest, MultiplicationCommutative) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    Complex result1 = z1 * z2;
    Complex result2 = z2 * z1;
    EXPECT_EQ(result1.real(), result2.real());
    EXPECT_EQ(result1.imaginary(), result2.imaginary());
}

TEST(ComplexTest, MultiplicationByI) {
    // (3 + 4i) * i = 3i + 4i² = 3i - 4 = -4 + 3i
    Complex z(3.0, 4.0);
    Complex i(0.0, 1.0);
    Complex result = z * i;
    EXPECT_EQ(result.real(), -4.0);
    EXPECT_EQ(result.imaginary(), 3.0);
}

// ============================================================================
// Pruebas de División
// ============================================================================

TEST(ComplexTest, Division) {
    // (3 + 4i) / (1 + 2i)
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    Complex result = z1 / z2;
    
    // Verificar que el resultado es aproximadamente (2.2 - 0.4i)
    EXPECT_NEAR(result.real(), 2.2, 1e-6);
    EXPECT_NEAR(result.imaginary(), -0.4, 1e-6);
}

TEST(ComplexTest, DivisionByOne) {
    Complex z(3.0, 4.0);
    Complex one(1.0, 0.0);
    Complex result = z / one;
    EXPECT_NEAR(result.real(), z.real(), 1e-9);
    EXPECT_NEAR(result.imaginary(), z.imaginary(), 1e-9);
}

TEST(ComplexTest, DivisionByZero) {
    Complex z(3.0, 4.0);
    Complex zero(0.0, 0.0);
    EXPECT_THROW(z / zero, std::invalid_argument);
}

TEST(ComplexTest, DivisionSelf) {
    Complex z(5.0, 3.0);
    Complex result = z / z;
    EXPECT_NEAR(result.real(), 1.0, 1e-9);
    EXPECT_NEAR(result.imaginary(), 0.0, 1e-9);
}

// ============================================================================
// Pruebas de Operadores Unarios
// ============================================================================

TEST(ComplexTest, UnaryPlus) {
    Complex z(3.0, 4.0);
    Complex result = +z;
    EXPECT_EQ(result.real(), z.real());
    EXPECT_EQ(result.imaginary(), z.imaginary());
}

TEST(ComplexTest, UnaryMinus) {
    Complex z(3.0, 4.0);
    Complex result = -z;
    EXPECT_EQ(result.real(), -3.0);
    EXPECT_EQ(result.imaginary(), -4.0);
}

TEST(ComplexTest, UnaryMinusDouble) {
    Complex z(3.0, 4.0);
    Complex result = -(-z);
    EXPECT_EQ(result.real(), z.real());
    EXPECT_EQ(result.imaginary(), z.imaginary());
}

// ============================================================================
// Pruebas de Operadores de Asignación
// ============================================================================

TEST(ComplexTest, AddAssignment) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    z1 += z2;
    EXPECT_EQ(z1.real(), 4.0);
    EXPECT_EQ(z1.imaginary(), 6.0);
}

TEST(ComplexTest, SubtractAssignment) {
    Complex z1(5.0, 8.0);
    Complex z2(2.0, 3.0);
    z1 -= z2;
    EXPECT_EQ(z1.real(), 3.0);
    EXPECT_EQ(z1.imaginary(), 5.0);
}

TEST(ComplexTest, MultiplyAssignment) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    z1 *= z2;
    EXPECT_EQ(z1.real(), -5.0);
    EXPECT_EQ(z1.imaginary(), 10.0);
}

TEST(ComplexTest, DivideAssignment) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    z1 /= z2;
    EXPECT_NEAR(z1.real(), 2.2, 1e-6);
    EXPECT_NEAR(z1.imaginary(), -0.4, 1e-6);
}

// ============================================================================
// Pruebas de Comparación
// ============================================================================

TEST(ComplexTest, EqualityOperator) {
    Complex z1(3.0, 4.0);
    Complex z2(3.0, 4.0);
    EXPECT_TRUE(z1 == z2);
}

TEST(ComplexTest, EqualityOperatorSelf) {
    Complex z(3.0, 4.0);
    EXPECT_TRUE(z == z);
}

TEST(ComplexTest, InequalityOperator) {
    Complex z1(3.0, 4.0);
    Complex z2(1.0, 2.0);
    EXPECT_TRUE(z1 != z2);
}

TEST(ComplexTest, NotEqualToItself) {
    Complex z(3.0, 4.0);
    EXPECT_FALSE(z != z);
}

TEST(ComplexTest, AlmostEqualWithinEpsilon) {
    Complex z1(3.0, 4.0);
    Complex z2(3.0 + 1e-10, 4.0 + 1e-10);
    EXPECT_TRUE(z1 == z2);  // Dentro de EPSILON
}

// ============================================================================
// Pruebas de Conversión a String
// ============================================================================

TEST(ComplexTest, ToStringRealOnly) {
    Complex z(5.0, 0.0);
    std::string expected = "5.00";
    EXPECT_EQ(z.toString(), expected);
}

TEST(ComplexTest, ToStringImaginaryOnly) {
    Complex z(0.0, 3.0);
    std::string str = z.toString();
    EXPECT_NE(str.find("3"), std::string::npos);  // Contiene 3
}

TEST(ComplexTest, ToStringBoth) {
    Complex z(3.0, 4.0);
    std::string str = z.toString();
    EXPECT_NE(str.find("3"), std::string::npos);  // Contiene 3
    EXPECT_NE(str.find("4"), std::string::npos);  // Contiene 4
}

// ============================================================================
// Pruebas de Propiedades Matemáticas
// ============================================================================

TEST(ComplexTest, ModulusSquareProperty) {
    Complex z(3.0, 4.0);
    // |z|² = z * conjugate(z)
    double modulusSquare = z.magnitude() * z.magnitude();
    Complex product = z * z.conjugate();
    EXPECT_NEAR(modulusSquare, product.real(), 1e-9);
    EXPECT_NEAR(0.0, product.imaginary(), 1e-9);
}

TEST(ComplexTest, ConjugateMultiplication) {
    Complex z(3.0, 4.0);
    Complex conj = z.conjugate();
    Complex product = z * conj;
    // El resultado debe ser real e igual a |z|²
    double expectedReal = z.magnitude() * z.magnitude();
    EXPECT_NEAR(product.real(), expectedReal, 1e-9);
    EXPECT_NEAR(product.imaginary(), 0.0, 1e-9);
}

// ============================================================================
// Pruebas de Casos Especiales
// ============================================================================

TEST(ComplexTest, VerySmallNumbers) {
    Complex z(1e-10, 1e-10);
    EXPECT_DOUBLE_EQ(z.real(), 1e-10);
    EXPECT_DOUBLE_EQ(z.imaginary(), 1e-10);
}

TEST(ComplexTest, VeryLargeNumbers) {
    Complex z(1e10, 1e10);
    EXPECT_DOUBLE_EQ(z.real(), 1e10);
    EXPECT_DOUBLE_EQ(z.imaginary(), 1e10);
}

TEST(ComplexTest, NegativeNumbers) {
    Complex z(-3.0, -4.0);
    EXPECT_DOUBLE_EQ(z.magnitude(), 5.0);
    EXPECT_EQ(z.real(), -3.0);
    EXPECT_EQ(z.imaginary(), -4.0);
}
