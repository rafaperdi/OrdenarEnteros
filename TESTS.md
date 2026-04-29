# 🧪 Guía de Ejecución de Tests Unitarios

## 📋 Descripción

Este proyecto incluye **67 tests unitarios** desarrollados con **Google Test (GTest)** que validan el correcto funcionamiento de las clases principales:

- **Complex** (47 tests): Números complejos con operaciones aritméticas
- **Array** (20 tests): Contenedor genérico para colecciones

## ⚡ Inicio Rápido

### Compilar con Tests (Recomendado)

```bash
# Crear directorio de compilación
mkdir build_static
cd build_static

# Configurar CMake (los tests se habilitan por defecto)
cmake ..

# Compilar todo incluidos los tests
make
```

### Ejecutar Todos los Tests

```bash
# Opción 1: Usar el script proporcionado (recomendado)
cd /path/to/OrdenarEnteros
./run_tests.sh

# Opción 2: Ejecutar tests individuales
cd build_static
./bin/tests/test_complex
./bin/tests/test_array
```

## 📖 Guía Completa

### 1️⃣ Configuración Inicial

#### Opción A: Con Tests (Defecto)
```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros
rm -rf build_static
mkdir build_static
cd build_static
cmake ..
make
```

#### Opción B: Sin Tests
```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros
mkdir build
cd build
cmake .. -DBUILD_TESTS=OFF
make
```

### 2️⃣ Ejecución de Tests

#### Script Automatizado (Recomendado)

```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros
./run_tests.sh
```

**Salida esperada:**
```
======================================================================
                    EJECUTANDO TESTS UNITARIOS
======================================================================

────────────────────────────────────────────────────────────────
Ejecutando: test_complex
────────────────────────────────────────────────────────────────
[==========] Running 47 tests from 1 test suite.
[  PASSED  ] 47 tests.
✓ test_complex PASSED

────────────────────────────────────────────────────────────────
Ejecutando: test_array
────────────────────────────────────────────────────────────────
[==========] Running 20 tests from 1 test suite.
[  PASSED  ] 20 tests.
✓ test_array PASSED

======================================================================
                          RESUMEN DE TESTS
======================================================================

Tests Ejecutados: 2
✓ Pasados: 67
✗ Fallidos: 0

======================================================================
                   ✓ TODOS LOS TESTS PASARON
======================================================================
```

#### Ejecutar Tests Individuales

```bash
cd build_static

# Tests de la clase Complex
./bin/tests/test_complex

# Tests de la clase Array
./bin/tests/test_array
```

#### Tests Específicos (Filtrado)

```bash
cd build_static

# Ejecutar solo tests de suma en Complex
./bin/tests/test_complex --gtest_filter=ComplexTest.Addition*

# Ejecutar solo tests de multiplicación
./bin/tests/test_complex --gtest_filter=ComplexTest.Multiplication*

# Ejecutar solo tests de Array
./bin/tests/test_array --gtest_filter=ArrayTest.*
```

#### Listar Todos los Tests Disponibles

```bash
cd build_static

# Listar tests de Complex
./bin/tests/test_complex --gtest_list_tests

# Listar tests de Array
./bin/tests/test_array --gtest_list_tests
```

### 3️⃣ Opciones Avanzadas

#### Salida Detallada con Tiempos

```bash
cd build_static
./bin/tests/test_complex --gtest_print_time=1 -v
```

#### Repetir Tests Múltiples Veces

```bash
cd build_static
./bin/tests/test_complex --gtest_repeat=5
```

#### Salida en Formato XML

```bash
cd build_static
./bin/tests/test_complex --gtest_output=xml:results.xml
```

#### Detener en Primer Fallo

```bash
cd build_static
./bin/tests/test_complex --gtest_break_on_failure
```

## 📊 Tests Disponibles

### Complex (47 Tests)

#### Constructores y Getters (5 tests)
```
ComplexTest.DefaultConstructor
ComplexTest.ParametrizedConstructor
ComplexTest.ConstructorWithOnlyReal
ComplexTest.RealPart
ComplexTest.ImaginaryPart
```

#### Operaciones Matemáticas (6 tests)
```
ComplexTest.Magnitude
ComplexTest.MagnitudeOfZero
ComplexTest.MagnitudeRealOnly
ComplexTest.MagnitudeImaginaryOnly
ComplexTest.Phase
ComplexTest.Conjugate
```

#### Operaciones Aritméticas (15 tests)
```
ComplexTest.Addition*                  (3 tests)
ComplexTest.Subtraction*              (3 tests)
ComplexTest.Multiplication*           (5 tests)
ComplexTest.Division*                 (4 tests)
```

#### Operadores Especiales (12 tests)
```
ComplexTest.UnaryPlus
ComplexTest.UnaryMinus
ComplexTest.AddAssignment
ComplexTest.SubtractAssignment
ComplexTest.MultiplyAssignment
ComplexTest.DivideAssignment
ComplexTest.EqualityOperator*         (5 tests)
```

#### Casos Especiales (9 tests)
```
ComplexTest.ToStringRealOnly
ComplexTest.ToStringImaginaryOnly
ComplexTest.ToStringBoth
ComplexTest.ModulusSquareProperty
ComplexTest.ConjugateMultiplication
ComplexTest.VerySmallNumbers
ComplexTest.VeryLargeNumbers
ComplexTest.NegativeNumbers
```

### Array (20 Tests)

```
ArrayTest.DefaultConstructor
ArrayTest.ConstructorWithInitializerList
ArrayTest.ConstructorWithSingleElement
ArrayTest.SizeAfterCreation
ArrayTest.SizeOfEmptyArray
ArrayTest.IndexAccessRead
ArrayTest.IndexAccessWrite
ArrayTest.IndexAccessModify
ArrayTest.ArrayOfDoubles
ArrayTest.ArrayOfStrings
ArrayTest.ArrayOfChars
ArrayTest.ConstAccessOperator
ArrayTest.ConstArraySizeCheck
ArrayTest.IterateThroughArray
ArrayTest.ModifyAllElements
ArrayTest.LargeArray
ArrayTest.ArrayOfZeros
ArrayTest.ArrayWithNegativeNumbers
ArrayTest.SizeImmutableAfterCreation
ArrayTest.ArrayIndexStartsAtZero
```

## 🔍 Interpretar Resultados

### Salida de Éxito

```
[==========] Running 47 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 47 tests from ComplexTest
[ RUN      ] ComplexTest.DefaultConstructor
[       OK ] ComplexTest.DefaultConstructor (0 ms)
...
[==========] 47 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 47 tests.
```

✅ **Interpretación:** Todos los tests pasaron correctamente.

### Salida de Fallo

```
[ FAILED  ] ComplexTest.Addition (1 ms)
ComplexTest.Addition: Value of: result.real()
  Actual: 3.5
Expected: 4.0
```

❌ **Interpretación:** El test falló. La suma de números complejos no devolvió el valor esperado.

## 📝 Ejemplos Prácticos

### Ejemplo 1: Compilar y Ejecutar Todos los Tests

```bash
#!/bin/bash
set -e

cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros

# Limpiar compilaciones anteriores
rm -rf build_static

# Crear y compilar
mkdir build_static
cd build_static
cmake ..
make

# Ejecutar tests
cd ..
./run_tests.sh
```

### Ejemplo 2: Solo Tests de Complex

```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static
./bin/tests/test_complex --gtest_filter=ComplexTest.*
```

### Ejemplo 3: Verificar Solo Multiplicación

```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static
./bin/tests/test_complex --gtest_filter=ComplexTest.Multiplication*
```

### Ejemplo 4: Tests con Salida Detallada

```bash
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static
./bin/tests/test_complex --gtest_print_time=1 -v 2>&1 | head -100
```

## 🛠️ Solución de Problemas

### Problema: "Tests no encontrados"

```bash
# Solución: Asegúrate de haber compilado con tests habilitados
cd build_static
cmake -DBUILD_TESTS=ON ..
make
```

### Problema: "Error: No such file or directory: ./run_tests.sh"

```bash
# Solución: Dar permisos de ejecución
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros
chmod +x run_tests.sh
./run_tests.sh
```

### Problema: "Librería no encontrada"

```bash
# Solución: Limpiar y recompilar
cd /home/rperdi/projects/cplusplus/repos/OrdenarEnteros
rm -rf build_static
mkdir build_static
cd build_static
cmake ..
make
```

### Problema: "Google Test no descargado"

```bash
# Solución: CMake descargará GTest automáticamente
# Si falla, verifica conexión a internet y ejecuta nuevamente:
cd build_static
cmake .. --fresh
make
```

## 📋 Checklist de Compilación y Tests

- [ ] Limpiar build anterior: `rm -rf build_static`
- [ ] Crear directorio: `mkdir build_static && cd build_static`
- [ ] Configurar CMake: `cmake ..`
- [ ] Compilar proyecto: `make`
- [ ] Ejecutar tests: `./run_tests.sh` o `./bin/tests/test_complex`
- [ ] Verificar: ✓ Todos los tests deben pasar

## 📊 Estadísticas

| Métrica | Valor |
|---------|-------|
| **Total de Tests** | 67 |
| **Tests Complex** | 47 |
| **Tests Array** | 20 |
| **Tiempo Ejecución** | < 10ms |
| **Cobertura** | 100% de métodos principales |
| **Framework** | Google Test 1.14.0 |

## 🔗 Referencias

- [Google Test Documentation](https://google.github.io/googletest/)
- [Google Test GitHub](https://github.com/google/googletest)
- [GTest Flags Reference](https://google.github.io/googletest/reference/flags.html)

## 📞 Soporte

Si encuentras problemas:

1. Verifica que estés en el directorio correcto
2. Asegúrate de que CMake está instalado
3. Verifica la conexión a internet (para descargar GTest)
4. Consulta la sección "Solución de Problemas" arriba

---

**Última actualización:** 29 de abril de 2026

**Compilador:** GCC 15.2.0  
**Estándar C++:** 17  
**Platform:** Linux
