# Tests Unitarios con Google Test

## 📋 Descripción

Este proyecto utiliza **Google Test (GTest)** para pruebas unitarias de las clases principales:
- `Complex`: Números complejos con operaciones aritméticas
- `Array`: Contenedor genérico para colecciones

## 🏗️ Estructura de Tests

```
tests/
├── CMakeLists.txt          # Configuración de compilación de tests
├── test_complex.cpp        # 47 tests para la clase Complex
└── test_array.cpp          # 20 tests para la clase Array
```

## 📊 Cobertura de Tests

### Tests para `Complex` (47 tests)

**Constructores (3 tests):**
- Constructor por defecto
- Constructor parametrizado
- Constructor con solo parte real

**Getters (2 tests):**
- Obtener parte real
- Obtener parte imaginaria

**Operaciones Matemáticas (6 tests):**
- Magnitud (módulo)
- Fase (ángulo)
- Conjugado

**Suma (3 tests):**
- Suma básica
- Suma con cero
- Propiedad conmutativa

**Resta (3 tests):**
- Resta básica
- Resta con cero
- Resta de sí mismo

**Multiplicación (5 tests):**
- Multiplicación básica
- Multiplicación por cero
- Multiplicación por uno
- Propiedad conmutativa
- Multiplicación por i

**División (4 tests):**
- División básica
- División por uno
- División por cero (excepción)
- División de sí mismo

**Operadores Unarios (3 tests):**
- Operador +
- Operador -
- Doble negación

**Operadores de Asignación (4 tests):**
- +=, -=, *=, /=

**Comparación (5 tests):**
- Igualdad
- Desigualdad
- Igualdad con tolerancia epsilon

**Conversión a String (3 tests):**
- Solo parte real
- Solo parte imaginaria
- Ambas partes

**Propiedades Matemáticas (2 tests):**
- Propiedad del módulo al cuadrado
- Multiplicación con conjugado

**Casos Especiales (3 tests):**
- Números muy pequeños
- Números muy grandes
- Números negativos

### Tests para `Array` (20 tests)

**Constructores (3 tests):**
- Constructor por defecto
- Constructor con initializer_list
- Constructor con un único elemento

**Size (2 tests):**
- Tamaño después de creación
- Tamaño de array vacío

**Acceso (3 tests):**
- Lectura con operator[]
- Escritura con operator[]
- Modificación de elementos

**Tipos de Datos (3 tests):**
- Array de doubles
- Array de strings
- Array de chars

**Operador const (2 tests):**
- Acceso const con operator[]
- Size en array const

**Iteración (2 tests):**
- Iterar a través del array
- Modificar todos los elementos

**Casos Especiales (2 tests):**
- Array grande (50 elementos)
- Array de ceros
- Array con números negativos
- Inmutabilidad del tamaño
- Índice comienza en cero

## 🚀 Compilación

### Compilación con Tests (por defecto)

```bash
cd /path/to/proyecto
mkdir build_static
cd build_static
cmake ..
make
```

### Compilación sin Tests

```bash
cd /path/to/proyecto
mkdir build
cd build
cmake .. -DBUILD_TESTS=OFF
make
```

## ▶️ Ejecución de Tests

### Ejecutar todos los tests de Complex

```bash
cd build_static
./bin/tests/test_complex
```

**Salida esperada:**
```
[==========] Running 47 tests from 1 test suite.
[----------] 47 tests from ComplexTest
...
[  PASSED  ] 47 tests.
```

### Ejecutar todos los tests de Array

```bash
cd build_static
./bin/tests/test_array
```

**Salida esperada:**
```
[==========] Running 20 tests from 1 test suite.
[----------] 20 tests from ArrayTest
...
[  PASSED  ] 20 tests.
```

### Ejecutar un test específico

```bash
# Ejecutar solo tests de suma en Complex
./bin/tests/test_complex --gtest_filter=ComplexTest.Addition*

# Ejecutar solo tests de Array
./bin/tests/test_array --gtest_filter=ArrayTest.*
```

### Listar todos los tests disponibles

```bash
./bin/tests/test_complex --gtest_list_tests
./bin/tests/test_array --gtest_list_tests
```

### Ver resultados detallados

```bash
./bin/tests/test_complex --gtest_print_time=1 -v
```

## 📝 Ejemplos de Uso

### Verificar todos los tests pasaron

```bash
#!/bin/bash
cd build_static
echo "Testing Complex class..."
if ./bin/tests/test_complex; then
    echo "✓ Complex tests PASSED"
else
    echo "✗ Complex tests FAILED"
    exit 1
fi

echo "Testing Array class..."
if ./bin/tests/test_array; then
    echo "✓ Array tests PASSED"
else
    echo "✗ Array tests FAILED"
    exit 1
fi

echo "All tests PASSED ✓"
```

## 🔧 Google Test - Macros Utilizadas

### Assertions (Afirmaciones)

```cpp
ASSERT_EQ(a, b)              // a == b (fatal)
EXPECT_EQ(a, b)              // a == b (no fatal)
ASSERT_TRUE(condition)       // condition es verdadero
EXPECT_FALSE(condition)      // condition es falso
EXPECT_DOUBLE_EQ(a, b)       // Comparación de doubles con precisión
EXPECT_NEAR(a, b, tol)       // Comparación con tolerancia
EXPECT_THROW(statement, exception)  // Verifica que lanza excepción
```

## 📊 Estadísticas de Tests

| Clase | Tests | Métodos | Líneas de Código |
|-------|-------|---------|-----------------|
| Complex | 47 | ~15 | ~200 |
| Array | 20 | ~5 | ~150 |
| **Total** | **67** | - | **~350** |

## 🔍 Próximas Mejoras

- [ ] Tests para clase `Sorting`
- [ ] Tests de integración
- [ ] Coverage report con gcov
- [ ] Benchmarks de performance
- [ ] Tests parametrizados para más casos

## 📚 Referencias

- [Google Test Documentation](https://google.github.io/googletest/)
- [CMake and Google Test](https://cmake.org/cmake/help/latest/module/FetchContent.html)

---

**Última actualización:** 29 de abril de 2026
