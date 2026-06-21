# Resumen técnico

OrdenarEnteros dispone de una única configuración CMake nativa para Windows y
Linux.

## Capacidades

- C++17 con MSVC, GCC o Clang.
- builds Debug, RelWithDebInfo y Release.
- biblioteca estática o compartida.
- x64, x86 y ARM64 en el script Windows.
- detección automática de Visual Studio, CMake, Ninja y vcpkg.
- presets portables para terminal, VS Code y CI.
- IPO/LTO automático y optimización de CPU optativa.
- ASan/UBSan optativos en GCC/Clang.
- 75 pruebas unitarias mediante CTest.
- instalación con paquete CMake exportado.

## Comandos principales

```powershell
.\build_windows_portable.cmd Release x64
.\build_windows_portable.cmd Debug x64 --tests
```

```bash
./build.sh release
./run_tests.sh
```

## Decisiones de portabilidad

- El sistema operativo se detecta; no se fuerza con una variable.
- `--native` está desactivado por defecto.
- cada generador/configuración usa su propia carpeta.
- las rutas no contienen nombres de usuario ni instalaciones fijas.
- vcpkg es opcional y tiene fallback a FetchContent para Google Test.

El directorio `src/` es histórico. La implementación activa está en `lib/` y
la aplicación principal en `app/`.
