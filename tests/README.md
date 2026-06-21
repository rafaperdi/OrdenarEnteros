# Pruebas unitarias

Los tres ejecutables de prueba se registran mediante
`gtest_discover_tests`, por lo que CTest conoce cada caso individual.

```text
tests/
├── test_array.cpp      # 20 casos
├── test_complex.cpp    # 47 casos
└── test_sorting.cpp    # 8 casos
```

Ejecución portable:

```bash
cmake --preset tests
cmake --build --preset tests
ctest --preset tests
```

Consulta [../TESTS.md](../TESTS.md) para Windows, filtros y solución de
dependencias.
