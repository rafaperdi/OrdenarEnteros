# INICIO RÁPIDO - OrdenarEnteros

Bienvenido a **OrdenarEnteros**, un proyecto profesional de C++ con librería dinámica configurable.

## 🚀 Inicio Rápido (30 segundos)

### Opción 1: Usar Script de Compilación (Recomendado)

```bash
cd /ruta/a/OrdenarEnteros
./build.sh dynamic    # Compilar (dinámica, Linux)
./build/bin/OrdenarEnteros   # Ejecutar
```

### Opción 2: Compilación Manual

```bash
cd /ruta/a/OrdenarEnteros
mkdir -p build && cd build
cmake ..
cmake --build .
../build/bin/OrdenarEnteros
```

## 📚 Ejemplos Rápidos

### Después de compilar, ejecutar:

```bash
# Programa principal (8 pruebas completas)
./build/bin/OrdenarEnteros

# Ejemplos individuales
./build/bin/examples/ejemplo1_basico
./build/bin/examples/ejemplo2_strings
./build/bin/examples/ejemplo3_objetos
```

## 🎯 Casos de Uso Comunes

### 1. Compilar para Linux (Dinámica)

```bash
./build.sh dynamic
# o manualmente:
cmake -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
```

**Resultado:** `build/lib/libordenamiento_lib.so`

### 2. Compilar para Linux (Estática)

```bash
./build.sh static
# o manualmente:
cmake -B build -DBUILD_SHARED_LIBS=OFF
cmake --build build
```

**Resultado:** `build/lib/libordenamiento_lib.a`

### 3. Compilar para Windows

```bash
./build.sh windows
# o manualmente:
cmake -B build -DTARGET_PLATFORM=Windows
cmake --build build --config Release
```

**Resultado:** `build\lib\ordenamiento_lib.dll`

### 4. Compilar en Modo Debug

```bash
./build.sh debug
# o manualmente:
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### 5. Compilar TODAS las versiones

```bash
./build.sh all
```

Genera 5 builds:
- `build/` - Linux dinámica
- `build_static/` - Linux estática
- `build_debug/` - Linux debug
- `build_windows/` - Windows dinámica
- `build_windows_static/` - Windows estática

## 📁 Estructura Principal

```
OrdenarEnteros/
├── lib/                    # Librería de ordenamiento
│   ├── include/           # Headers públicos
│   │   ├── array.h
│   │   └── sorting.h
│   └── src/
│       └── sorting.cpp
├── app/                    # Aplicación principal
│   └── main.cpp
├── examples/               # 3 ejemplos de uso
├── build.sh               # Script de compilación (recomendado)
├── CMakeLists.txt         # Configuración raíz
├── README.md              # Documentación completa
├── GUIA_COMPILACION.md    # Guía detallada
└── ESTRUCTURA_PROYECTO.md # Estructura interna
```

## 🔧 Configuración CMake (Opciones)

```cmake
BUILD_SHARED_LIBS     # ON (dinámica) | OFF (estática)
TARGET_PLATFORM       # "Linux" | "Windows"
CMAKE_BUILD_TYPE      # "Debug" | "Release"
```

## 💡 Ejemplo de Uso en tu Código

```cpp
#include "array.h"
#include "sorting.h"
#include <iostream>

int main() {
    // Crear array de enteros
    Array<int> numeros{5, 2, 8, 1, 9};
    
    // Ordenar
    ordenar(numeros);
    
    // Imprimir
    std::cout << "Ordenado: ";
    numeros.print();  // [1, 2, 5, 8, 9]
    
    return 0;
}
```

## 📖 Documentación

- **[README.md](README.md)** - Documentación completa
- **[GUIA_COMPILACION.md](GUIA_COMPILACION.md)** - Guía detallada de compilación
- **[ESTRUCTURA_PROYECTO.md](ESTRUCTURA_PROYECTO.md)** - Estructura interna del proyecto

## ✨ Características

- ✅ **Templates Genéricos** - Funciona con cualquier tipo
- ✅ **Multiplataforma** - Linux y Windows
- ✅ **Configurable** - Dinámica o estática
- ✅ **Fácil de Usar** - API simple
- ✅ **Profesional** - Estructura lista para producción

## 🎓 Tipos Soportados

```cpp
// Tipos primitivos
Array<int> numeros{1, 2, 3};
Array<double> decimales{1.1, 2.2};

// Strings
Array<std::string> palabras{"a", "b"};

// Objetos customizados
class MiClase { ... };
Array<MiClase> objetos{...};
```

## 🔗 Compilación Rápida

| Necesito | Comando |
|----------|---------|
| Dinámica (Linux) | `./build.sh dynamic` |
| Estática (Linux) | `./build.sh static` |
| Windows | `./build.sh windows` |
| Todas las versiones | `./build.sh all` |
| Limpiar | `./build.sh clean` |
| Ayuda | `./build.sh help` |

## ⚠️ Requerimientos

- CMake 3.10+
- C++17
- Compilador: GCC, Clang o MSVC

## 🆘 Problemas Comunes

### "cmake: command not found"
```bash
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake           # macOS
```

### "Permission denied" (script)
```bash
chmod +x build.sh
```

### Librería dinámica no encontrada (Linux)
```bash
LD_LIBRARY_PATH=./build/lib ./build/bin/OrdenarEnteros
```

## 📊 Tamaños

| Tipo | Tamaño |
|------|--------|
| Librería dinámica (.so) | ~17 KB |
| Librería estática (.a) | ~11 KB |
| Ejecutable (dinámica) | ~74 KB |
| Ejecutable (estática) | ~74 KB |

## 🚀 Próximos Pasos

1. ✅ Compilar con `./build.sh dynamic`
2. ✅ Ejecutar `./build/bin/OrdenarEnteros`
3. ✅ Ver ejemplos en `./build/bin/examples/`
4. 📖 Leer [README.md](README.md) para más detalles
5. 🔧 Personalizaciones en [GUIA_COMPILACION.md](GUIA_COMPILACION.md)

---

**¡Listo para empezar! Compila, prueba y distribuye.** 🎉

```bash
./build.sh dynamic && ./build/bin/OrdenarEnteros
```
