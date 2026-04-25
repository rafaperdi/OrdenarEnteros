# OrdenarEnteros - Librería Dinámica Configurable

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

## 🚀 Compilación

### Compilación Básica (Dinámica - Linux)

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

El ejecutable estará en: `build/bin/OrdenarEnteros`
La librería estará en: `build/lib/libordenamiento_lib.so`

### Opciones de Compilación

#### 1️⃣ Librería Estática (Linux)
```bash
cmake -B build -DBUILD_SHARED_LIBS=OFF
cmake --build build
```
Genera: `build/lib/libordenamiento_lib.a`

#### 2️⃣ Librería Dinámica (Linux - Default)
```bash
cmake -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
```
Genera: `build/lib/libordenamiento_lib.so`

#### 3️⃣ Para Windows (Dinámica)
```bash
cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=ON
cmake --build build
```
Genera: `build\bin\OrdenarEnteros.exe`, `build\lib\ordenamiento_lib.dll`

#### 4️⃣ Para Windows (Estática)
```bash
cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF
cmake --build build
```
Genera: `build\lib\ordenamiento_lib.lib`

#### 5️⃣ Modo Debug
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

#### 6️⃣ Modo Release (Optimizaciones)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Combinaciones de Opciones

```bash
# Windows + Estática + Release
cmake -B build -DTARGET_PLATFORM=Windows \
               -DBUILD_SHARED_LIBS=OFF \
               -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Linux + Dinámica + Debug
cmake -B build -DTARGET_PLATFORM=Linux \
               -DBUILD_SHARED_LIBS=ON \
               -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## 🏃 Ejecución

### Linux
```bash
./build/bin/OrdenarEnteros
```

### Windows
```bash
.\build\bin\OrdenarEnteros.exe
```

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
| `CMAKE_BUILD_TYPE` | `Release` | `Debug` / `Release` | Modo de compilación |
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
- **Compilador**:
  - Linux: GCC 7.0+ o Clang 5.0+
  - Windows: MSVC 2017+ o GCC/Clang en MinGW

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

