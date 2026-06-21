# Guía de compilación

## Requisitos

- CMake 3.21 o posterior.
- Compilador compatible con C++17.
- Windows: Visual Studio con las herramientas C++.
- Linux: GCC o Clang; Ninja es recomendado, no obligatorio.
- Git y red solo si los tests necesitan descargar Google Test.

## Diseño portable

CMake usa `WIN32`, `UNIX`, `CMAKE_SYSTEM_NAME` y el compilador detectado. La
plataforma no se selecciona con `TARGET_PLATFORM`. Para cross-compilar se usa
`CMAKE_TOOLCHAIN_FILE`.

Cada perfil tiene una carpeta independiente bajo `out/build`, evitando mezclar
generadores, arquitecturas o configuraciones.

## Windows

### Build recomendado

```powershell
.\build_windows_portable.cmd Release x64
```

El script:

1. Busca Visual Studio con `vswhere`.
2. Carga `vcvarsall.bat` para x64, x86 o ARM64.
3. añade CMake, Ninja y vcpkg al `PATH` del proceso;
4. usa Ninja y recurre a NMake si Ninja no está disponible;
5. aplica el toolchain de vcpkg cuando lo encuentra;
6. configura runtime MSVC estático y LTO compatible;
7. compila en paralelo.

El entorno solo afecta al proceso del script y a sus hijos.

### Sintaxis

```text
build_windows_portable.cmd [Release|RelWithDebInfo|Debug] [x64|x86|arm64] [opciones]
```

Opciones:

- `--static`: biblioteca estática; predeterminado.
- `--shared`: DLL.
- `--tests`: compila y ejecuta los tests.
- `--native`: activa optimización para la CPU local.
- `--vcpkg`: exige vcpkg.
- `--no-vcpkg`: no usa el toolchain de vcpkg.

Ejemplos:

```powershell
.\build_windows_portable.cmd RelWithDebInfo x64
.\build_windows_portable.cmd Release arm64 --shared
.\build_windows_portable.cmd Debug x86 --tests
```

Salidas:

```text
out\build\windows-x64-release\bin\OrdenarEnteros.exe
out\build\windows-x64-release\bin\examples\*.exe
out\build\windows-x64-release\lib\ordenamiento_lib.lib
```

## Linux y otros Unix

```bash
./build.sh release
./out/build/release/bin/OrdenarEnteros
```

Perfiles:

```bash
./build.sh debug
./build.sh dev
./build.sh release
./build.sh release-shared
./build.sh tests
```

Los scripts son envoltorios de los presets y prefieren Ninja cuando está
instalado y la carpeta aún no está configurada. El uso directo es equivalente:

```bash
cmake --preset release
cmake --build --preset release
```

CMake elige el generador disponible. También puede especificarse uno en la
primera configuración:

```bash
cmake --preset release -G Ninja
```

## Tests

```bash
cmake --preset tests
cmake --build --preset tests
ctest --preset tests
```

En Windows:

```powershell
.\build_windows_portable.cmd Debug x64 --tests
```

Se busca primero `GTest::gtest_main` mediante `find_package`. Si no existe,
FetchContent descarga Google Test v1.17.0.

## Rendimiento y diagnóstico

Release habilita IPO/LTO si el compilador lo soporta. Las opciones estándar
`-O3` o `/O2` las aporta CMake, sin duplicar flags manualmente.

Optimización para la máquina local:

```bash
./build.sh release -DORDENARENT_NATIVE_OPTIMIZATION=ON
```

Sanitizers en GCC/Clang:

```bash
cmake --preset debug -DORDENARENT_ENABLE_SANITIZERS=ON
cmake --build --preset debug
```

No combines `--native` con binarios destinados a equipos heterogéneos.

## Biblioteca compartida y estática

```bash
./build.sh release
./build.sh release-shared
```

En Linux la variante compartida genera `.so`; en Windows, `.dll` y su
biblioteca de importación.

## Instalación

```bash
cmake --install out/build/release --prefix out/install
```

Se instalan cabeceras, biblioteca y los archivos de paquete CMake para usar:

```cmake
find_package(OrdenarEnteros CONFIG REQUIRED)
target_link_libraries(app PRIVATE OrdenarEnteros::ordenamiento_lib)
```

## Solución de problemas

### CMake no se reconoce en Windows

Usa `build_windows_portable.cmd`; no depende del `PATH` global.

### No se encuentra Visual Studio

Comprueba que esté instalada la carga de trabajo C++ y que exista:

```text
%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe
```

### El generador no coincide

No reutilices una carpeta con otro generador. Los presets y el script Windows
ya separan las carpetas por perfil y arquitectura.

### Google Test no puede descargarse

Instálalo mediante vcpkg/paquetes del sistema o configura con
`-DBUILD_TESTING=OFF`.

### Quiero máxima portabilidad

Usa Release sin `--native`. El runtime estático de MSVC reduce dependencias del
ejecutable de Windows, pero las DLL del sistema siguen siendo necesarias.
