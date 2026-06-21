# Inicio rapido - OrdenarEnteros

Esta guia contiene el camino mas corto para compilar y ejecutar el proyecto.
Para todas las opciones y la solucion de problemas, consulta
[GUIA_COMPILACION.md](GUIA_COMPILACION.md).

## Windows: compilacion recomendada

Requisitos:

- Visual Studio Community 2026 instalado en
  `C:\Program Files\Microsoft Visual Studio\18\Community`
- Componente de desarrollo de escritorio con C++
- CMake y Ninja incluidos con Visual Studio

Desde PowerShell o `cmd.exe`, en la raiz del proyecto:

```powershell
.\build_windows_portable.cmd
```

El script genera una compilacion `Release` para Windows x64 con:

- libreria estatica
- runtime de MSVC estatico
- ejemplos incluidos
- tests unitarios deshabilitados

Segun el generador guardado en la carpeta de compilacion, el ejecutable estara
en una de estas rutas:

```text
build_windows_portable\bin\Release\OrdenarEnteros.exe
build_windows_portable\bin\OrdenarEnteros.exe
```

Para localizarlo y ejecutarlo desde PowerShell:

```powershell
$exe = Get-ChildItem .\build_windows_portable\bin -Recurse -Filter OrdenarEnteros.exe |
    Select-Object -First 1
& $exe.FullName
```

## Linux: compilacion recomendada

Requisitos:

- CMake 3.10 o posterior
- compilador compatible con C++17, como GCC o Clang
- Git y acceso a Internet si se compilan los tests por primera vez

```bash
cmake -S . -B build_linux \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=ON \
  -DBUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_linux --parallel
./build_linux/bin/OrdenarEnteros
```

## Compilar y ejecutar tests

Google Test se descarga durante la primera configuracion, por lo que este paso
requiere acceso a Internet si aun no esta almacenado localmente.

### Windows con Visual Studio

Ejecuta los comandos desde un Developer PowerShell o Developer Command Prompt:

```powershell
cmake -S . -B build_tests -A x64 `
  -DTARGET_PLATFORM=Windows `
  -DBUILD_SHARED_LIBS=OFF `
  -DBUILD_TESTS=ON

cmake --build build_tests --config Release --parallel
ctest --test-dir build_tests -C Release --output-on-failure
```

### Linux

```bash
cmake -S . -B build_tests \
  -DTARGET_PLATFORM=Linux \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build_tests --parallel
ctest --test-dir build_tests --output-on-failure
```

## Error de generador de CMake

Una carpeta de compilacion solo puede pertenecer a un generador. Por ejemplo,
no se puede reutilizar una carpeta creada con Visual Studio usando Ninja.

El script `build_windows_portable.cmd` reutiliza automaticamente el generador
guardado. Para comandos manuales, usa una carpeta diferente para cada
generador:

```text
build_msvc
build_ninja
build_linux
build_tests
```

Si aparece el mensaje `Does not match the generator used previously`, consulta
la seccion de solucion de problemas de
[GUIA_COMPILACION.md](GUIA_COMPILACION.md).
