# OrdenarEnteros

Biblioteca educativa en C++17 con un contenedor `Array<T>`, algoritmos de
ordenamiento genéricos y una clase `Complex`. El mismo proyecto CMake compila
de forma nativa en Windows y Linux; no es necesario indicar manualmente la
plataforma.

## Inicio rápido

### Windows

Requiere Visual Studio Community, Professional o Enterprise con la carga de
trabajo **Desarrollo de escritorio con C++**.

```powershell
.\build_windows_portable.cmd Release x64
.\out\build\windows-x64-release\bin\OrdenarEnteros.exe
```

El script localiza Visual Studio con `vswhere`, inicializa MSVC y añade al
`PATH` del proceso CMake, Ninja y vcpkg cuando están disponibles. No modifica
permanentemente el `PATH` del sistema.

### Linux

```bash
./build.sh release
./out/build/release/bin/OrdenarEnteros
```

El script prefiere Ninja si está instalado; en caso contrario utiliza el
generador predeterminado de CMake.

También se pueden usar directamente los presets:

```bash
cmake --preset release
cmake --build --preset release
```

## Perfiles disponibles

| Perfil | Uso |
|---|---|
| `debug` | Desarrollo sin optimizaciones |
| `dev` | `RelWithDebInfo` con tests |
| `release` | Release, biblioteca estática y optimización portable |
| `release-shared` | Release con `.dll` o `.so` |
| `tests` | Debug con todos los tests |

Windows ofrece las mismas variantes mediante argumentos:

```powershell
.\build_windows_portable.cmd Debug x64 --tests
.\build_windows_portable.cmd Release arm64 --shared
.\build_windows_portable.cmd Release x64 --native
```

`--native` puede mejorar el rendimiento en el equipo local, pero produce un
binario menos portable. Release ya habilita IPO/LTO automáticamente cuando el
compilador lo soporta.

## Tests

El proyecto contiene 75 casos de Google Test para `Array`, `Complex` y los
algoritmos de ordenamiento.

```powershell
# Windows
.\build_windows_portable.cmd Debug x64 --tests
```

```bash
# Linux
./run_tests.sh
```

CMake intenta primero localizar Google Test instalado, por ejemplo mediante
vcpkg. Si no lo encuentra, descarga v1.17.0 durante la primera configuración.

## Uso

```cpp
#include "array.h"
#include "sorting.h"

#include <functional>

Array<int> values{8, 3, 5, 1, 9};
ordenar(values);
ordenar(values, std::greater<>{});
values.print();
```

`ordenar` y `quickSort` usan `std::sort`, cuyo algoritmo introspectivo ofrece
`O(n log n)` en el peor caso. `selectionSort` permanece disponible de forma
explícita para demostraciones educativas.

`Array<T>` proporciona `begin`, `end`, `data`, `at`, `operator[]`, `size` y
`empty`, por lo que se integra con los algoritmos estándar.

## Opciones CMake

| Opción | Predeterminado | Descripción |
|---|---:|---|
| `BUILD_SHARED_LIBS` | `OFF` en presets | Biblioteca estática o compartida |
| `BUILD_TESTING` | `OFF` | Compilar tests |
| `ORDENARENT_BUILD_APP` | `ON` | Compilar la aplicación |
| `ORDENARENT_BUILD_EXAMPLES` | `ON` | Compilar ejemplos |
| `ORDENARENT_ENABLE_IPO` | `ON` | IPO/LTO en configuraciones optimizadas |
| `ORDENARENT_NATIVE_OPTIMIZATION` | `OFF` | Optimizar para la CPU local |
| `ORDENARENT_ENABLE_SANITIZERS` | `OFF` | ASan y UBSan con GCC/Clang |
| `ORDENARENT_WARNINGS_AS_ERRORS` | `OFF` | Tratar warnings como errores |
| `MSVC_STATIC_RUNTIME` | `OFF` | Usar `/MT` con MSVC |

Para cross-compilar se debe usar un archivo toolchain de CMake; no se simula
otra plataforma mediante una variable.

## Instalar y reutilizar

```bash
cmake --install out/build/release --prefix out/install
```

Desde otro proyecto CMake:

```cmake
find_package(OrdenarEnteros CONFIG REQUIRED)
target_link_libraries(mi_programa PRIVATE OrdenarEnteros::ordenamiento_lib)
```

Configura `CMAKE_PREFIX_PATH` con la ruta de instalación si no es una ubicación
estándar.

## Estructura

- `lib/`: biblioteca y cabeceras públicas.
- `app/`: aplicación de demostración.
- `examples/`: cuatro ejemplos independientes.
- `tests/`: pruebas de Google Test.
- `src/`: versión histórica independiente, no forma parte del build raíz.
- `CMakePresets.json`: perfiles portables.

Consulta [INICIO_RAPIDO.md](INICIO_RAPIDO.md) para el camino corto y
[GUIA_COMPILACION.md](GUIA_COMPILACION.md) para todas las opciones.
