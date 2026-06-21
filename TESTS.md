# Tests

El proyecto contiene 75 casos de Google Test:

| Suite | Casos |
|---|---:|
| `ComplexTest` | 47 |
| `ArrayTest` | 20 |
| `SortingTest` | 8 |

## Ejecutar todo

Windows:

```powershell
.\build_windows_portable.cmd Debug x64 --tests
```

Linux:

```bash
./run_tests.sh
```

Con presets:

```bash
cmake --preset tests
cmake --build --preset tests
ctest --preset tests
```

## Filtrar

```bash
ctest --preset tests -R Sorting
./out/build/tests/bin/tests/test_complex --gtest_filter=ComplexTest.Division*
```

En Windows el segundo comando equivalente se encuentra en:

```text
out\build\windows-x64-debug\bin\tests\test_complex.exe
```

## Dependencia Google Test

CMake intenta usar una instalación existente mediante `find_package(GTest
CONFIG)`. Esto permite aprovechar vcpkg o el gestor de paquetes del sistema.
Si no está instalada, se descarga Google Test v1.17.0 con FetchContent.

Para compilar sin tests:

```bash
cmake --preset release
```

o añade `-DBUILD_TESTING=OFF` a una configuración manual.

## Qué se valida

- construcción, acceso e iteración de `Array<T>`;
- operaciones y casos límite de `Complex`;
- arrays vacíos y unitarios;
- valores repetidos y ya ordenados;
- orden ascendente y descendente;
- compatibilidad de `selectionSort`, `ordenar` y `quickSort`.
