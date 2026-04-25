# OrdenarEnteros

Proyecto de C++ con algoritmos de ordenamiento genéricos usando **Templates**, que funcionan con cualquier tipo de dato primitivo, strings y objetos customizados.

## Características

✨ **Genérico con Templates C++**: Funciona con cualquier tipo de dato que implemente el operador `<`
- ✅ Tipos primitivos: `int`, `double`, `float`, `char`, etc.
- ✅ Strings: `std::string`
- ✅ Objetos personalizados: cualquier clase con operador de comparación definido

🔄 **Múltiples Algoritmos**:
- Selection Sort (búsqueda del mínimo)
- Quick Sort (ordenamiento rápido)

⚙️ **Comparadores Customizados**: Permite ordenar por diferentes criterios
- Ordenamiento ascendente/descendente
- Comparadores personalizados para objetos

## Archivos

- `src/main.cpp` - Función `main()` con 8 pruebas completas de diferentes tipos
- `src/Array.h` - Template de clase `Array<T>` con implementación inline
- `src/int_sort.h` - Templates de funciones de ordenamiento genéricas
- `src/int_sort.cpp` - Comentarios sobre la implementación con templates
- `src/CMakeLists.txt` - Configuración CMake (C++17)

## Compilar

```bash
cd src/build
cmake ..
make
```

## Ejecutar

```bash
./build/OrdenarEnteros
```

## Ejemplos de Uso

### 1. Ordenar Integers
```cpp
Array<int> numeros{8, 3, 5, 1, 9, 2, 7, 4};
ordenar(numeros);
```

### 2. Ordenar Strings
```cpp
Array<std::string> palabras{"zebra", "apple", "mango", "banana"};
ordenar(palabras);
```

### 3. Ordenar Doubles
```cpp
Array<double> decimales{3.14, 2.71, 1.41, 4.44};
ordenar(decimales);
```

### 4. Ordenar Objetos Customizados
```cpp
class Persona {
public:
    std::string nombre;
    int edad;
    bool operator<(const Persona& otro) const {
        return edad < otro.edad;
    }
};

Array<Persona> personas{
    Persona("Alice", 30),
    Persona("Bob", 25)
};
ordenar(personas);  // Ordena por edad
```

### 5. Usar Comparador Customizado
```cpp
struct ComparadorPorNombre {
    bool operator()(const Persona& a, const Persona& b) const {
        return a.nombre < b.nombre;
    }
};

ordenar(personas, ComparadorPorNombre());  // Ordena por nombre
```

### 6. Orden Descendente
```cpp
template <typename T>
struct ComparadorDescendente {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

ordenar(numeros, ComparadorDescendente<int>());
```

### 7. Usar QuickSort
```cpp
Array<int> numeros{8, 3, 5, 1, 9};
quickSort(numeros);
```

## Pruebas Incluidas

El programa `main.cpp` incluye 8 pruebas demostrativas:

1. ✅ Selection Sort de Integers (ascendente)
2. ✅ Selection Sort de Doubles (ascendente)
3. ✅ Selection Sort de Strings (alfabético)
4. ✅ Ordenamiento de objetos Persona por edad
5. ✅ Ordenamiento de objetos Persona por nombre (comparador customizado)
6. ✅ Ordenamiento de Integers (descendente)
7. ✅ Ordenamiento de Strings (descendente)
8. ✅ QuickSort de Integers

## Requerimientos

- C++17 o superior
- CMake 3.10 o superior
- Compilador compatible (g++, clang, MSVC, etc.)

## Notas de Implementación

- Los **templates** se definen completamente en los archivos header (`.h`)
- La compilación instantía los templates solo para los tipos realmente utilizados
- Los objetos customizados deben implementar el operador `operator<` para ordenamiento ascendente
- Se pueden pasar comparadores como segundo parámetro para lógica de comparación personalizada

