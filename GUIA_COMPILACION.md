# GuíaDeCompilación.md - OrdenarEnteros

## Guía Completa de Compilación

Este documento explica todas las opciones de compilación disponibles para el proyecto OrdenarEnteros.

## 📋 Tabla de Contenidos

1. [Compilación Básica](#compilación-básica)
2. [Opciones CMake](#opciones-cmake)
3. [Compilación para Linux](#compilación-para-linux)
4. [Compilación para Windows](#compilación-para-windows)
5. [Compilación Condicional](#compilación-condicional)
6. [Estructura de Salida](#estructura-de-salida)
7. [Troubleshooting](#troubleshooting)

## Compilación Básica

### 1️⃣ Compilación por Defecto (Librería Dinámica - Linux)

```bash
cd /ruta/a/OrdenarEnteros
mkdir -p build
cd build
cmake ..
cmake --build .
```

**Resultado:**
- Ejecutable: `build/bin/OrdenarEnteros`
- Librería: `build/lib/libordenamiento_lib.so.1.0.0`
- Enlace simbólico: `build/lib/libordenamiento_lib.so`

## Opciones CMake

### 1. `BUILD_SHARED_LIBS` (Por defecto: ON)

Controla si se compila como librería dinámica o estática.

| Valor | Resultado | Archivo |
|-------|-----------|---------|
| `ON` | Dinámica | `.so` (Linux), `.dll` (Windows) |
| `OFF` | Estática | `.a` (Linux), `.lib` (Windows) |

### 2. `TARGET_PLATFORM` (Por defecto: Linux)

Define la plataforma destino de compilación.

| Valor | Descripción | Compilador Típico |
|-------|-------------|-------------------|
| `Linux` | Linux/Unix | GCC o Clang |
| `Windows` | Windows | MSVC, MinGW, etc. |

### 3. `CMAKE_BUILD_TYPE` (Por defecto: Release)

Tipo de compilación con diferentes optimizaciones.

| Valor | Descripción | Optimizaciones |
|-------|-------------|-----------------|
| `Debug` | Debug | `-g -O0` (GCC), símbolos de depuración |
| `Release` | Producción | `-O3 -march=native` (GCC), optimizaciones máximas |

### 4. `EXECUTABLE_OUTPUT_DIR` (Por defecto: `build/bin`)

Ruta personalizada para ejecutables.

### 5. `LIBRARY_OUTPUT_DIR` (Por defecto: `build/lib`)

Ruta personalizada para librerías.

## Compilación para Linux

### Librería Dinámica (Por Defecto)

```bash
cmake -B build -DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=ON
cmake --build build
```

**Genera:**
- `build/bin/OrdenarEnteros`
- `build/lib/libordenamiento_lib.so`

### Librería Estática

```bash
cmake -B build -DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=OFF
cmake --build build
```

**Genera:**
- `build/bin/OrdenarEnteros`
- `build/lib/libordenamiento_lib.a`

### Modo Debug (Linux)

```bash
cmake -B build -DTARGET_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Modo Release Optimizado (Linux)

```bash
cmake -B build -DTARGET_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Compilación para Windows

### Desde Windows con MSVC

#### Librería Dinámica

```bash
cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=ON
cmake --build build --config Release
```

**Genera:**
- `build\bin\OrdenarEnteros.exe`
- `build\lib\ordenamiento_lib.dll`
- `build\lib\ordenamiento_lib.lib` (import library)

#### Librería Estática

```bash
cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release
```

**Genera:**
- `build\bin\OrdenarEnteros.exe`
- `build\lib\ordenamiento_lib.lib`

### Desde Linux Compilando para Windows (MinGW)

```bash
# Requiere toolchain de MinGW instalado
cmake -B build \
    -DCMAKE_TOOLCHAIN_FILE=/ruta/a/mingw-toolchain.cmake \
    -DTARGET_PLATFORM=Windows \
    -DBUILD_SHARED_LIBS=ON

cmake --build build
```

## Compilación Condicional

### Combinaciones Comunes

#### 1. Linux + Estática + Debug

```bash
cmake -B build \
    -DTARGET_PLATFORM=Linux \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE=Debug

cmake --build build
```

#### 2. Linux + Dinámica + Release

```bash
cmake -B build \
    -DTARGET_PLATFORM=Linux \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release

cmake --build build
```

#### 3. Windows + Estática + Release

```bash
cmake -B build \
    -DTARGET_PLATFORM=Windows \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release
```

#### 4. Windows + Dinámica + Debug

```bash
cmake -B build \
    -DTARGET_PLATFORM=Windows \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Debug

cmake --build build --config Debug
```

### Directorios de Salida Personalizados

```bash
cmake -B build \
    -DEXECUTABLE_OUTPUT_DIR="/ruta/custom/bin" \
    -DLIBRARY_OUTPUT_DIR="/ruta/custom/lib"

cmake --build build
```

## Estructura de Salida

Después de compilar, la estructura típica es:

### Compilación Dinámica (Linux)
```
build/
├── bin/
│   ├── OrdenarEnteros           (ejecutable principal)
│   └── examples/
│       ├── ejemplo1_basico
│       ├── ejemplo2_strings
│       └── ejemplo3_objetos
└── lib/
    ├── libordenamiento_lib.so.1.0.0
    ├── libordenamiento_lib.so.1     (enlace simbólico)
    └── libordenamiento_lib.so       (enlace simbólico)
```

### Compilación Estática (Linux)
```
build/
├── bin/
│   ├── OrdenarEnteros           (ejecutable principal, binario grande)
│   └── examples/
│       ├── ejemplo1_basico      (binarios también grandes)
│       ├── ejemplo2_strings
│       └── ejemplo3_objetos
└── lib/
    └── libordenamiento_lib.a
```

### Compilación (Windows)
```
build\
├── bin\
│   ├── OrdenarEnteros.exe
│   └── examples\
│       ├── ejemplo1_basico.exe
│       ├── ejemplo2_strings.exe
│       └── ejemplo3_objetos.exe
└── lib\
    ├── ordenamiento_lib.dll
    ├── ordenamiento_lib.lib     (import library)
    └── ...
```

## Limpieza y Reconstrucción

### Limpiar Build (mantiene CMakeCache)

```bash
cd build
cmake --build . --target clean
```

### Reconstruir Completamente

```bash
cd /ruta/a/OrdenarEnteros
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

## Ejecución

### Linux

```bash
# Ejecutable principal
./build/bin/OrdenarEnteros

# Ejemplos
./build/bin/examples/ejemplo1_basico
./build/bin/examples/ejemplo2_strings
./build/bin/examples/ejemplo3_objetos
```

### Windows

```bash
# Ejecutable principal
.\build\bin\OrdenarEnteros.exe

# Ejemplos
.\build\bin\examples\ejemplo1_basico.exe
.\build\bin\examples\ejemplo2_strings.exe
.\build\bin\examples\ejemplo3_objetos.exe
```

### Ejecución con Librería Dinámica en Linux

Si la librería dinámica no está en la ruta del sistema:

```bash
# Opción 1: Usar LD_LIBRARY_PATH
LD_LIBRARY_PATH=./build/lib ./build/bin/OrdenarEnteros

# Opción 2: Instalar la librería
sudo cp build/lib/libordenamiento_lib.so.1.0.0 /usr/local/lib/
sudo ldconfig

# Ahora ejecutar normalmente
./build/bin/OrdenarEnteros
```

## Troubleshooting

### Error: "CMake not found"

```bash
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake           # macOS
choco install cmake          # Windows (Chocolatey)
```

### Error: "C++ compiler not found"

**Linux:**
```bash
sudo apt-get install build-essential  # Ubuntu/Debian
```

**macOS:**
```bash
xcode-select --install
```

**Windows:**
- Descargar Visual Studio Community con herramientas de C++
- O instalar MinGW/GCC

### Error: "libordenamiento_lib.so: cannot open shared object file"

Solución:
```bash
# Opción 1
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/lib

# Opción 2
sudo ldconfig -p | grep libordenamiento_lib
```

### Error: "Permission denied" (ejecutable no ejecutable)

```bash
chmod +x build/bin/OrdenarEnteros
```

### Compilación muy lenta

Usar compilación paralela:
```bash
cmake --build build -j 4  # 4 núcleos
# o
make -j 4
```

## Verificación de Compilación

### Verificar Tipo de Librería (Linux)

```bash
# Para dinámica
ldd build/lib/libordenamiento_lib.so

# Para estática
file build/lib/libordenamiento_lib.a

# Para ejecutable
ldd build/bin/OrdenarEnteros
```

### Verificar Símbolos (Linux)

```bash
nm build/lib/libordenamiento_lib.so | grep ordenar
nm build/lib/libordenamiento_lib.a | grep ordenar
```

### Verificar Size (Linux)

```bash
# Dinámico
ls -lh build/lib/libordenamiento_lib.so
ls -lh build/bin/OrdenarEnteros

# Estático
ls -lh build/lib/libordenamiento_lib.a
ls -lh build/bin/OrdenarEnteros
```

---

## Cheat Sheet Rápido

```bash
# ===== LINUX =====

# Dinámica (default)
cmake -B build && cmake --build build

# Estática
cmake -B build -DBUILD_SHARED_LIBS=OFF && cmake --build build

# Debug dinámico
cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build

# Release estático
cmake -B build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release && cmake --build build

# ===== WINDOWS =====

# Dinámica
cmake -B build -DTARGET_PLATFORM=Windows && cmake --build build --config Release

# Estática
cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF && cmake --build build --config Release
```

---

**¡Listo para compilar! Elige la opción que mejor se ajuste a tus necesidades.** 🚀
