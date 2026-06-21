# Inicio rápido

## Windows

Instala Visual Studio con **Desarrollo de escritorio con C++** y ejecuta:

```powershell
.\build_windows_portable.cmd Release x64
.\out\build\windows-x64-release\bin\OrdenarEnteros.exe
```

No hace falta añadir CMake a mano al `PATH`: el script detecta Visual Studio
Community/Professional/Enterprise, carga MSVC y usa su CMake, Ninja y vcpkg.

Tests:

```powershell
.\build_windows_portable.cmd Debug x64 --tests
```

## Linux

Requiere CMake 3.21+, un compilador C++17 y, preferiblemente, Ninja.

```bash
chmod +x build.sh run_tests.sh
./build.sh release
./out/build/release/bin/OrdenarEnteros
```

Tests:

```bash
./run_tests.sh
```

## Variantes útiles

```bash
./build.sh debug
./build.sh dev
./build.sh release-shared
./build.sh release -DORDENARENT_NATIVE_OPTIMIZATION=ON
```

La optimización nativa solo debe usarse cuando el binario vaya a ejecutarse en
la misma CPU o en una compatible.

Más detalles: [GUIA_COMPILACION.md](GUIA_COMPILACION.md).
