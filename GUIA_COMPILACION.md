# Guia de compilacion

Esta es la referencia de compilacion del proyecto `OrdenarEnteros`.

## Requisitos

El proyecto requiere:

- CMake 3.10 o posterior
- un compilador compatible con C++17
- Git y acceso a Internet para descargar Google Test la primera vez que se
  configura una compilacion con `BUILD_TESTS=ON`

En Windows se recomienda Visual Studio con la carga de trabajo de desarrollo de
escritorio con C++. El script incluido esta preparado para Visual Studio
Community 2026 instalado en:

```text
C:\Program Files\Microsoft Visual Studio\18\Community
```

## Compilacion recomendada para Windows

Desde PowerShell o `cmd.exe`, situado en la raiz del repositorio:

```powershell
.\build_windows_portable.cmd
```

El script:

- inicializa el entorno x64 de MSVC
- reutiliza el generador almacenado si ya existe una caché de CMake
- usa Ninja al crear por primera vez la carpeta
- configura una compilacion `Release`
- genera una libreria estatica
- enlaza estaticamente el runtime de MSVC mediante `/MT`
- compila la aplicacion principal y los cuatro ejemplos
- deshabilita los tests unitarios

Configuracion equivalente:

```text
TARGET_PLATFORM=Windows
BUILD_SHARED_LIBS=OFF
MSVC_STATIC_RUNTIME=ON
BUILD_TESTS=OFF
```

### Salidas

Con el generador de Visual Studio:

```text
build_windows_portable\bin\Release\OrdenarEnteros.exe
build_windows_portable\bin\examples\Release\ejemplo1_basico.exe
build_windows_portable\bin\examples\Release\ejemplo2_strings.exe
build_windows_portable\bin\examples\Release\ejemplo3_objetos.exe
build_windows_portable\bin\examples\Release\ejemplo4_complejos.exe
build_windows_portable\lib\Release\ordenamiento_lib.lib
```

Con Ninja, las mismas salidas no incluyen el subdirectorio `Release`:

```text
build_windows_portable\bin\OrdenarEnteros.exe
build_windows_portable\bin\examples\ejemplo1_basico.exe
build_windows_portable\lib\ordenamiento_lib.lib
```

### Ejecutar la aplicacion

Con la carpeta actual configurada mediante Visual Studio:

```powershell
.\build_windows_portable\bin\Release\OrdenarEnteros.exe
```

Comando independiente del generador:

```powershell
$exe = Get-ChildItem .\build_windows_portable\bin -Recurse -Filter OrdenarEnteros.exe |
    Select-Object -First 1
& $exe.FullName
```

## Compilacion manual para Windows

Ejecuta estos comandos desde un Developer PowerShell o Developer Command Prompt
de Visual Studio.

### Visual Studio: estatica y Release

```powershell
cmake -S . -B build_msvc -A x64 `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=OFF `
  -DMSVC_STATIC_RUNTIME=ON `
  -DBUILD_TESTS=OFF

cmake --build build_msvc --config Release --parallel
.\build_msvc\bin\Release\OrdenarEnteros.exe
```

### Visual Studio: dinamica y Release

```powershell
cmake -S . -B build_msvc_shared -A x64 `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=ON `
  -DBUILD_TESTS=OFF

cmake --build build_msvc_shared --config Release --parallel
.\build_msvc_shared\bin\Release\OrdenarEnteros.exe
```

La DLL y su biblioteca de importacion se generan dentro de los directorios de
salida de la configuracion `Release`.

### Ninja: estatica y Release

```powershell
cmake -S . -B build_ninja -G Ninja `
  -DCMAKE_BUILD_TYPE=Release `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=OFF `
  -DMSVC_STATIC_RUNTIME=ON `
  -DBUILD_TESTS=OFF

cmake --build build_ninja --parallel
.\build_ninja\bin\OrdenarEnteros.exe
```

## Compilacion para Linux

### Dinamica y Release

```bash
cmake -S . -B build_linux \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=ON \
  -DBUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_linux --parallel
./build_linux/bin/OrdenarEnteros
```

Genera `build_linux/lib/libordenamiento_lib.so`.

### Estatica y Debug

```bash
cmake -S . -B build_linux_debug \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build build_linux_debug --parallel
./build_linux_debug/bin/OrdenarEnteros
```

Genera `build_linux_debug/lib/libordenamiento_lib.a`.

El script Bash `build.sh` tambien ofrece configuraciones predefinidas para
entornos Unix:

```bash
./build.sh help
./build.sh dynamic
./build.sh static
./build.sh debug
```

## Tests unitarios

Los tests usan Google Test y estan activados por defecto. Para evitar descargas
durante una compilacion normal, especifica `-DBUILD_TESTS=OFF`.

### Windows con Visual Studio

```powershell
cmake -S . -B build_tests -A x64 `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=OFF `
  -DBUILD_TESTS=ON

cmake --build build_tests --config Release --parallel
ctest --test-dir build_tests -C Release --output-on-failure
```

### Linux o Ninja

```bash
cmake -S . -B build_tests \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_tests --parallel
ctest --test-dir build_tests --output-on-failure
```

## Opciones CMake

| Variable | Valor por defecto | Descripcion |
|---|---|---|
| `TARGET_PLATFORM` | `Linux` | Plataforma logica: `Linux` o `Windows` |
| `BUILD_SHARED_LIBS` | `ON` | `ON` crea libreria dinamica; `OFF`, estatica |
| `BUILD_TESTS` | `ON` | Compila los tests y descarga Google Test si es necesario |
| `MSVC_STATIC_RUNTIME` | `OFF` | Con MSVC, usa `/MT` en lugar del runtime dinamico |
| `CMAKE_BUILD_TYPE` | sin valor | Configuracion para generadores de una sola configuracion, como Ninja |
| `EXECUTABLE_OUTPUT_DIR` | `<build>/bin` | Directorio base de ejecutables |
| `LIBRARY_OUTPUT_DIR` | `<build>/lib` | Directorio base de librerias |

`CMAKE_BUILD_TYPE` no selecciona la configuracion al usar Visual Studio. Con ese
generador debe pasarse `--config Debug` o `--config Release` al compilar y `-C`
al ejecutar `ctest`.

## Generadores y carpetas de compilacion

CMake guarda el generador dentro de `CMakeCache.txt`. No reutilices una misma
carpeta con generadores diferentes.

Ejemplo correcto:

```text
build_msvc       -> Visual Studio
build_ninja      -> Ninja
build_linux      -> Unix Makefiles o Ninja en Linux
build_tests      -> compilacion con tests
```

Para conocer el generador de una carpeta existente en PowerShell:

```powershell
Select-String -Path .\build_windows_portable\CMakeCache.txt `
  -Pattern '^CMAKE_GENERATOR:'
```

## Solucion de problemas

### `Does not match the generator used previously`

La carpeta ya fue configurada con otro generador. Usa otra carpeta:

```powershell
cmake -S . -B build_ninja_nuevo -G Ninja
```

Si necesitas regenerar una carpeta desde cero, elimina solo una carpeta de
compilacion que hayas identificado y quieras descartar. No elimines el codigo
fuente.

### `cmake` no se reconoce en PowerShell

Abre un Developer PowerShell de Visual Studio o usa
`build_windows_portable.cmd`, que invoca el CMake incluido con Visual Studio.

### El script no encuentra Visual Studio

Revisa `VS_ROOT` al inicio de `build_windows_portable.cmd`. Debe apuntar a la
instalacion real de Visual Studio.

### Google Test no se puede descargar

Configura sin tests:

```powershell
cmake -S . -B build_sin_tests -DBUILD_TESTS=OFF
```

Para compilar tests, habilita el acceso a Internet durante la primera
configuracion o reutiliza una carpeta que ya tenga Google Test descargado.

### No encuentro el ejecutable en Windows

Visual Studio agrega `Debug` o `Release` a las rutas; Ninja no lo hace:

```powershell
Get-ChildItem . -Recurse -Filter OrdenarEnteros.exe
```

## Verificacion rapida

La compilacion recomendada para Windows queda verificada cuando ambos comandos
terminan con codigo de salida `0`:

```powershell
.\build_windows_portable.cmd
.\build_windows_portable\bin\Release\OrdenarEnteros.exe
```

Si la carpeta fue creada con Ninja, usa
`.\build_windows_portable\bin\OrdenarEnteros.exe` para el segundo comando.
