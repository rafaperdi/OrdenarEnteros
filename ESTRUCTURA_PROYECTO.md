# Estructura del proyecto

```text
OrdenarEnteros/
├── CMakeLists.txt
├── CMakePresets.json
├── build_windows_portable.cmd
├── build.sh
├── run_tests.sh
├── cmake/
│   └── OrdenarEnterosConfig.cmake.in
├── lib/
│   ├── include/
│   │   ├── array.h
│   │   ├── complex.h
│   │   └── sorting.h
│   └── src/
│       ├── complex.cpp
│       └── sorting.cpp
├── app/
├── examples/
├── tests/
├── src/                    # implementación histórica independiente
└── out/                    # builds nuevos; no versionado
```

## Targets

| Target | Tipo | Responsabilidad |
|---|---|---|
| `ordenamiento_lib` | biblioteca | API pública y `Complex` |
| `OrdenarEnteros` | ejecutable | demostración principal |
| `ejemplo*` | ejecutables | ejemplos mínimos |
| `test_*` | ejecutables | pruebas Google Test |

El alias exportado para otros proyectos es
`OrdenarEnteros::ordenamiento_lib`.

## Dependencias

```text
app / examples / tests
          │
          ▼
OrdenarEnteros::ordenamiento_lib
          │
          ├── Array<T> y algoritmos (cabeceras)
          └── Complex (biblioteca compilada)
```

## Configuración

La raíz centraliza:

- C++17 sin extensiones específicas del compilador.
- warnings equivalentes en MSVC, GCC y Clang.
- rutas uniformes `bin/` y `lib/`.
- IPO/LTO en configuraciones optimizadas.
- runtime MSVC estático opcional.
- sanitizers opcionales.
- instalación y exportación CMake.

Los subdirectorios solo declaran sus fuentes y enlaces.

## Directorio histórico `src/`

`src/` conserva una versión anterior autónoma. No se añade desde el
`CMakeLists.txt` raíz y no afecta a los builds modernos. El código mantenido es
el de `lib/`, `app/`, `examples/` y `tests/`.

## Artefactos

Los builds nuevos se generan en `out/build/<perfil>` o, en Windows,
`out/build/windows-<arquitectura>-<configuración>`. El árbol `out/` está
ignorado por Git.
