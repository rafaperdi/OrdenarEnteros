# OrdenarEnteros - Librería de ordenamiento configurable

Proyecto profesional de C++ con algoritmos de ordenamiento genéricos usando **Templates**. Permite compilar como librería dinámica o estática, y configurable para Windows o Linux.

## 🎯 Características

✨ **Templates Genéricos**: Funciona con cualquier tipo de dato primitivo, strings y objetos customizados
🔄 **Múltiples Algoritmos**: Selection Sort y Quick Sort
⚙️ **Comparadores Customizados**: Permite ordenar por diferentes criterios
📦 **Librería Dinámica/Estática**: Configurable en CMake
🖥️ **Multiplataforma**: Compilable para Linux y Windows
🔧 **Fácil de Usar**: API simple y clara

## 📁 Estructura del Proyecto

```
OrdenarEnteros/
├── CMakeLists.txt                    # Configuración raíz (opciones de compilación)
├── README.md
│
├── lib/                              # Librería de ordenamiento
│   ├── CMakeLists.txt
│   ├── include/
│   │   ├── array.h                   # Template Array<T>
│   │   └── sorting.h                 # Funciones de ordenamiento
│   └── src/
│       └── sorting.cpp               # Instantiación de templates
│
└── app/                              # Aplicación de prueba
    ├── CMakeLists.txt
    └── main.cpp                      # Pruebas exhaustivas

build/                                # Directorio de compilación
├── bin/                              # Ejecutables generados
└── lib/                              # Librerías generadas
```

## Compilación

La guía breve está en [INICIO_RAPIDO.md](INICIO_RAPIDO.md) y todas las
variantes, rutas de salida y soluciones a errores están documentadas en
[GUIA_COMPILACION.md](GUIA_COMPILACION.md).

### Windows recomendado

Desde PowerShell o `cmd.exe`:

```powershell
.\build_windows_portable.cmd
```

Este script compila para Windows x64 en `Release`, con librería estática,
runtime estático de MSVC, ejemplos incluidos y tests deshabilitados.

Con la carpeta actualmente configurada mediante Visual Studio, el ejecutable
queda en:

```powershell
.\build_windows_portable\bin\Release\OrdenarEnteros.exe
```

Si el script crea la carpeta mediante Ninja, queda en:

```powershell
.\build_windows_portable\bin\OrdenarEnteros.exe
```

### Linux recomendado

```bash
cmake -S . -B build_linux \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=ON \
  -DBUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_linux --parallel
./build_linux/bin/OrdenarEnteros
```

### Tests

Los tests usan Google Test. La primera configuración con `BUILD_TESTS=ON`
requiere Git y acceso a Internet.

Windows con Visual Studio:

```powershell
cmake -S . -B build_tests -A x64 `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=OFF `
  -DBUILD_TESTS=ON

cmake --build build_tests --config Release --parallel
ctest --test-dir build_tests -C Release --output-on-failure
```

Linux:

```bash
cmake -S . -B build_tests \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_tests --parallel
ctest --test-dir build_tests --output-on-failure
```

### Importante: generadores de CMake

No reutilices una carpeta de compilación con generadores distintos. Por
ejemplo, una carpeta creada con Visual Studio no puede reconfigurarse con
Ninja. Usa carpetas separadas como `build_msvc`, `build_ninja` y
`build_tests`.

## 📚 Ejemplos de Uso

### 1. Ordenar Integers
```cpp
#include "array.h"
#include "sorting.h"

Array<int> numeros{8, 3, 5, 1, 9, 2, 7, 4};
ordenar(numeros);
numeros.print();  // [1, 2, 3, 4, 5, 7, 8, 9]
```

### 2. Ordenar Strings
```cpp
Array<std::string> palabras{"zebra", "apple", "mango"};
ordenar(palabras);
palabras.print();  // [apple, mango, zebra]
```

### 3. Ordenar Objetos Customizados
```cpp
class Persona {
public:
    std::string nombre;
    int edad;
    
    bool operator<(const Persona& otro) const {
        return edad < otro.edad;
    }
};

Array<Persona> personas{
    Persona("Alice", 30),
    Persona("Bob", 25)
};

ordenar(personas);  // Ordena por edad
```

### 4. Usar Comparador Personalizado
```cpp
struct ComparadorPorNombre {
    bool operator()(const Persona& a, const Persona& b) const {
        return a.nombre < b.nombre;
    }
};

ordenar(personas, ComparadorPorNombre());  // Ordena por nombre
```

### 5. Orden Descendente
```cpp
template <typename T>
struct Descendente {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

ordenar(numeros, Descendente<int>());  // Descendente
```

### 6. Usar QuickSort
```cpp
Array<int> numeros{8, 3, 5, 1, 9};
quickSort(numeros);
```

## 🧪 Pruebas Incluidas

El programa `main.cpp` incluye 8 pruebas exhaustivas:

1. ✅ Selection Sort de Integers (ascendente)
2. ✅ Selection Sort de Doubles (ascendente)
3. ✅ Selection Sort de Strings (alfabético)
4. ✅ Ordenamiento de objetos Persona por edad
5. ✅ Ordenamiento de objetos Persona por nombre
6. ✅ Ordenamiento de Integers (descendente)
7. ✅ Ordenamiento de Strings (descendente)
8. ✅ QuickSort de Integers

Ejecutar:
```bash
./build/bin/OrdenarEnteros
```

## 📝 Variables CMake Disponibles

| Variable | Valor Default | Opciones | Descripción |
|----------|---------------|----------|-------------|
| `BUILD_SHARED_LIBS` | `ON` | `ON` / `OFF` | Librería dinámica o estática |
| `TARGET_PLATFORM` | `Linux` | `Linux` / `Windows` | Plataforma destino |
| `BUILD_TESTS` | `ON` | `ON` / `OFF` | Compilar tests con Google Test |
| `MSVC_STATIC_RUNTIME` | `OFF` | `ON` / `OFF` | Usar runtime estático de MSVC (`/MT`) |
| `CMAKE_BUILD_TYPE` | Sin valor | `Debug` / `Release` | Modo para Ninja, Makefiles y otros generadores de una configuración |
| `EXECUTABLE_OUTPUT_DIR` | `build/bin` | Ruta personalizada | Salida de ejecutables |
| `LIBRARY_OUTPUT_DIR` | `build/lib` | Ruta personalizada | Salida de librerías |

## 🔧 API de la Librería

### Clase: `Array<T>`

```cpp
class Array {
public:
    Array(std::initializer_list<T> valores);
    
    size_t size() const noexcept;
    T& operator[](size_t indice);
    const T& operator[](size_t indice) const;
    void print() const;
};
```

### Funciones: Ordenamiento

```cpp
// Selection Sort - comparación por defecto
template <typename T>
void ordenar(Array<T>& arreglo);

// Selection Sort - comparador personalizado
template <typename T, typename Comparador>
void ordenar(Array<T>& arreglo, Comparador comp);

// Quick Sort
template <typename T>
void quickSort(Array<T>& arreglo, int izquierda = 0, int derecha = -1);
```

## 🔗 Enlazado con la Librería

Si deseas usar esta librería en otros proyectos:

### Enlazado Dinámico (Runtime)
```cmake
find_library(ORDENAMIENTO_LIB ordenamiento_lib PATHS /ruta/a/lib)
target_link_libraries(tu_proyecto PRIVATE ${ORDENAMIENTO_LIB})
```

### Enlazado Estático (Compile-time)
```cmake
target_link_libraries(tu_proyecto PRIVATE /ruta/a/libordenamiento_lib.a)
```

## 📋 Requerimientos

- **CMake**: 3.10 o superior
- **C++**: C++17 o superior
- **Tests**: Git y acceso a Internet durante la primera descarga de Google Test
- **Compilador**:
  - Linux: GCC 7.0+ o Clang 5.0+
  - Windows: MSVC con herramientas de desarrollo de escritorio con C++

## 🎓 Conceptos Implementados

- ✅ Templates genéricos en C++
- ✅ Programación orientada a objetos
- ✅ Compilación condicional con CMake
- ✅ Librerías compartidas/dinámicas
- ✅ Librerías estáticas
- ✅ Compilación multiplataforma
- ✅ Optimizaciones específicas de plataforma

## 📄 Licencia

Este proyecto es de código abierto y educativo.

## 👨‍💻 Uso en la Industria

Esta estructura es similar a la de proyectos profesionales reales:
- **Separación librería/aplicación**: Fácil mantenimiento
- **Compilación configurable**: Requisito común en DevOps
- **Soporte multiplataforma**: Esencial para distribución
- **Templates**: Estándar en C++ moderno

---

**¡Listo para usar! Compila, prueba y distribuye tu librería.** 🚀

