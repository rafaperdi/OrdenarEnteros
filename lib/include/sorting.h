#pragma once

#include "array.h"
#include <algorithm>
#include <cstddef>

// Función de ordenamiento genérica con comparador por defecto
template <typename T>
void ordenar(Array<T>& arreglo) {
    const std::size_t n = arreglo.size();
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t minimo = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (arreglo[j] < arreglo[minimo]) {
                minimo = j;
            }
        }
        if (minimo != i) {
            std::swap(arreglo[i], arreglo[minimo]);
        }
    }
}

// Función de ordenamiento genérica con comparador customizado
template <typename T, typename Comparador>
void ordenar(Array<T>& arreglo, Comparador comp) {
    const std::size_t n = arreglo.size();
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t minimo = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (comp(arreglo[j], arreglo[minimo])) {
                minimo = j;
            }
        }
        if (minimo != i) {
            std::swap(arreglo[i], arreglo[minimo]);
        }
    }
}

template <typename T>
void quickSortRange(Array<T>& arreglo, std::ptrdiff_t izquierda, std::ptrdiff_t derecha) {
    if (izquierda < derecha) {
        const T pivote = arreglo[static_cast<std::size_t>(derecha)];
        std::ptrdiff_t i = izquierda - 1;

        for (std::ptrdiff_t j = izquierda; j < derecha; ++j) {
            if (arreglo[static_cast<std::size_t>(j)] < pivote) {
                ++i;
                std::swap(arreglo[static_cast<std::size_t>(i)],
                          arreglo[static_cast<std::size_t>(j)]);
            }
        }

        const std::ptrdiff_t pivote_indice = i + 1;
        std::swap(arreglo[static_cast<std::size_t>(pivote_indice)],
                  arreglo[static_cast<std::size_t>(derecha)]);
        quickSortRange(arreglo, izquierda, pivote_indice - 1);
        quickSortRange(arreglo, pivote_indice + 1, derecha);
    }
}

template <typename T>
void quickSort(Array<T>& arreglo) {
    if (arreglo.size() < 2) {
        return;
    }

    quickSortRange(arreglo, 0, static_cast<std::ptrdiff_t>(arreglo.size() - 1));
}
