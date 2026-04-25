# ESTRUCTURA DEL PROYECTO - OrdenarEnteros

## 📂 Árbol de Directorios

```
OrdenarEnteros/
│
├── CMakeLists.txt                          # RAÍZ: Configuración global con opciones
├── README.md                               # Documentación principal
├── GUIA_COMPILACION.md                     # Guía completa de compilación
│
├── lib/                                    # 📦 LIBRERÍA COMPARTIDA
│   ├── CMakeLists.txt                     # Configuración de la librería
│   ├── include/
│   │   ├── array.h                        # Template: Clase Array<T>
│   │   └── sorting.h                      # Templates: Funciones de ordenamiento
│   └── src/
│       └── sorting.cpp                    # Instantiación de templates (para .so/.dll)
│
├── app/                                    # 🖥️ APLICACIÓN PRINCIPAL
│   ├── CMakeLists.txt                     # Configuración de la aplicación
│   └── main.cpp                           # Programa principal con 8 pruebas
│
├── examples/                               # 📚 EJEMPLOS DE USO
│   ├── CMakeLists.txt                     # Configuración de ejemplos
│   ├── ejemplo1_basico.cpp                # Ordenar enteros básico
│   ├── ejemplo2_strings.cpp               # Ordenar strings
│   └── ejemplo3_objetos.cpp               # Ordenar objetos customizados
│
├── build/                                  # 🔨 COMPILACIÓN DINÁMICA (Generado)
│   ├── bin/
│   │   ├── OrdenarEnteros                 # Ejecutable principal
│   │   └── examples/
│   │       ├── ejemplo1_basico
│   │       ├── ejemplo2_strings
│   │       └── ejemplo3_objetos
│   └── lib/
│       ├── libordenamiento_lib.so.1.0.0   # Librería dinámica (versionada)
│       ├── libordenamiento_lib.so.1       # Enlace simbólico
│       └── libordenamiento_lib.so         # Enlace simbólico
│
├── build_static/                           # 🔨 COMPILACIÓN ESTÁTICA (Generado)
│   ├── bin/
│   │   ├── OrdenarEnteros                 # Ejecutable (binario más grande)
│   │   └── examples/
│   │       ├── ejemplo1_basico
│   │       ├── ejemplo2_strings
│   │       └── ejemplo3_objetos
│   └── lib/
│       └── libordenamiento_lib.a          # Librería estática
│
├── src/                                    # ⚠️ DIRECTORIO ANTIGUO (obsoleto)
│   ├── Array.h
│   ├── int_sort.h
│   ├── int_sort.cpp
│   ├── main.cpp
│   └── CMakeLists.txt
│
└── .vscode/                                # Configuración VS Code
```

## 📋 Descripción de Archivos

### Configuración (CMakeLists.txt)

| Archivo | Propósito |
|---------|-----------|
| `CMakeLists.txt` (raíz) | Configuración global con opciones BUILD_SHARED_LIBS, TARGET_PLATFORM, etc. |
| `lib/CMakeLists.txt` | Define la librería ordenamiento_lib |
| `app/CMakeLists.txt` | Define el ejecutable OrdenarEnteros |
| `examples/CMakeLists.txt` | Define los 3 ejemplos |

### Librería (lib/)

| Archivo | Propósito | Tipo |
|---------|-----------|------|
| `lib/include/array.h` | Template genérico Array<T> | Header only |
| `lib/include/sorting.h` | Templates de funciones de ordenamiento | Header only |
| `lib/src/sorting.cpp` | Instantiación de templates para compilación | Implementación |

### Aplicación (app/)

| Archivo | Propósito | Descripción |
|---------|-----------|-------------|
| `app/main.cpp` | Programa principal | 8 pruebas completas de toda la funcionalidad |

### Ejemplos (examples/)

| Archivo | Propósito | Demuestra |
|---------|-----------|----------|
| `ejemplo1_basico.cpp` | Ordenamiento básico | Ordenar integers |
| `ejemplo2_strings.cpp` | Strings y descendente | Comparadores customizados |
| `ejemplo3_objetos.cpp` | Objetos Producto | Objetos customizados con múltiples criterios |

## 🏗️ Configuraciones de Compilación

### Compilación Dinámica (Linux)

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

**Resultado:**
```
build/
├── bin/OrdenarEnteros
└── lib/libordenamiento_lib.so
```

### Compilación Estática (Linux)

```bash
mkdir -p build
cd build
cmake .. -DBUILD_SHARED_LIBS=OFF
cmake --build .
```

**Resultado:**
```
build/
├── bin/OrdenarEnteros          (Binario independiente, puede ejecutarse sin librería)
└── lib/libordenamiento_lib.a
```

### Compilación para Windows

```bash
mkdir -p build
cd build
cmake .. -DTARGET_PLATFORM=Windows
cmake --build . --config Release
```

**Resultado:**
```
build\
├── bin\OrdenarEnteros.exe
└── lib\ordenamiento_lib.dll
```

## 📦 Variables CMake Disponibles

```cmake
BUILD_SHARED_LIBS          # ON (dinámica) | OFF (estática)
TARGET_PLATFORM            # "Linux" | "Windows"
CMAKE_BUILD_TYPE           # "Debug" | "Release"
EXECUTABLE_OUTPUT_DIR      # ${CMAKE_BINARY_DIR}/bin
LIBRARY_OUTPUT_DIR         # ${CMAKE_BINARY_DIR}/lib
```

## 🔗 Dependencias Entre Módulos

```
app/main.cpp
    ↓ (incluye)
lib/include/array.h  +  lib/include/sorting.h
    ↓ (depende de)
lib/src/sorting.cpp
    ↓ (compila a)
libordenamiento_lib.so / libordenamiento_lib.a
    ↓ (enlaza)
OrdenarEnteros (ejecutable)
```

## ⚙️ Proceso de Compilación

### 1. Fase de Configuración (cmake ..)

CMake:
1. Detecta compilador (GCC, Clang, MSVC)
2. Lee CMakeLists.txt raíz
3. Lee opciones de compilación
4. Configura compilación por plataforma
5. Lee subdirectorios (lib/, app/, examples/)
6. Genera archivos de compilación (Makefile o .sln)

### 2. Fase de Compilación (cmake --build .)

Compilador:
1. Compila `lib/src/sorting.cpp` → objeto compilado
2. Crea librería: linking → `lib/libordenamiento_lib.so` o `.a`
3. Compila `app/main.cpp` → objeto compilado
4. Enlaza con librería → `bin/OrdenarEnteros`
5. Compila ejemplos → objetos compilados
6. Enlaza ejemplos con librería → `bin/examples/*`

## 📊 Tamaños Típicos

| Archivo | Tipo | Tamaño |
|---------|------|--------|
| `libordenamiento_lib.so` | Dinámica | ~17 KB |
| `libordenamiento_lib.a` | Estática | ~11 KB |
| `OrdenarEnteros` (dinámico) | Ejecutable + dinámica | ~74 KB + 17 KB |
| `OrdenarEnteros` (estático) | Ejecutable incluido | ~74 KB |

## 🔍 Cómo Usar la Librería en Otro Proyecto

### Opción 1: Enlazado Dinámico (Runtime)

```cpp
// tuproyecto/main.cpp
#include "array.h"
#include "sorting.h"

int main() {
    Array<int> numeros{5, 2, 8, 1};
    ordenar(numeros);
}
```

```cmake
# tuproyecto/CMakeLists.txt
find_library(ORDENAMIENTO_LIB ordenamiento_lib 
    PATHS /ruta/a/OrdenarEnteros/build/lib)

add_executable(tuapp main.cpp)
target_link_libraries(tuapp PRIVATE ${ORDENAMIENTO_LIB})
target_include_directories(tuapp PRIVATE /ruta/a/OrdenarEnteros/lib/include)
```

Compilar:
```bash
cmake -B build
cmake --build build
```

Ejecutar:
```bash
LD_LIBRARY_PATH=/ruta/a/OrdenarEnteros/build/lib ./build/tuapp
```

### Opción 2: Enlazado Estático (Compile-time)

```cmake
# Mismo código, pero con librería estática
target_link_libraries(tuapp PRIVATE /ruta/a/OrdenarEnteros/build/lib/libordenamiento_lib.a)
```

Ahora el ejecutable funciona sin necesidad de la librería .so

## 🎯 Flujo de Desarrollo

```
1. Clonar/Descargar proyecto
   ↓
2. mkdir build && cd build
   ↓
3. cmake ..                    (detecta opciones por defecto)
   ↓
4. cmake --build .            (compila todo)
   ↓
5. ./bin/OrdenarEnteros        (ejecuta programa)
   ↓
6. ./bin/examples/*            (ejecuta ejemplos)
```

## 🛠️ Personalización

### Cambiar tipo de librería después de compilar

```bash
cd build
rm -rf CMakeCache.txt CMakeFiles
cmake .. -DBUILD_SHARED_LIBS=OFF
cmake --build .
```

### Cambiar plataforma destino

```bash
cd build
rm -rf CMakeCache.txt CMakeFiles
cmake .. -DTARGET_PLATFORM=Windows
cmake --build .
```

### Compilación paralela

```bash
cmake --build . -j 4  # 4 núcleos
```

## ✅ Verificación

Después de compilar, verificar:

```bash
# ¿Se generaron todos los binarios?
ls -l build/bin/
ls -l build/lib/

# ¿Funcionan los ejemplos?
./build/bin/examples/ejemplo1_basico
./build/bin/examples/ejemplo2_strings
./build/bin/examples/ejemplo3_objetos

# ¿Se ejecuta la app principal?
./build/bin/OrdenarEnteros
```

---

## 📝 Notas Importantes

1. **Templates**: Los archivos `.h` contienen implementación completa
2. **Multiplataforma**: Automático según compilador detectado
3. **Versionado de librería**: Soporta múltiples versiones simultáneamente
4. **Instalación**: Puede hacerse con `cmake --install build`

---

**Estructura lista para proyectos profesionales** ✨
