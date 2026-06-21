#pragma once

#include "array.h"

#include <algorithm>
#include <functional>
#include <utility>

// Ordenamiento recomendado. std::sort usa un algoritmo introspectivo con
// complejidad O(n log n) en el peor caso y suele superar a implementaciones
// manuales de quicksort.
template <typename T, typename Compare>
void ordenar(Array<T>& values, Compare compare) {
    std::sort(values.begin(), values.end(), std::move(compare));
}

template <typename T>
void ordenar(Array<T>& values) {
    ordenar(values, std::less<>{});
}

// Selection sort se conserva con nombre explicito para fines educativos.
template <typename T, typename Compare>
void selectionSort(Array<T>& values, Compare compare) {
    for(auto current = values.begin(); current != values.end(); ++current) {
        const auto selected = std::min_element(current, values.end(), compare);
        if(selected != current) {
            std::iter_swap(current, selected);
        }
    }
}

template <typename T>
void selectionSort(Array<T>& values) {
    selectionSort(values, std::less<>{});
}

// API historica: ahora delega en la implementacion robusta de la biblioteca
// estandar y tambien admite comparadores personalizados.
template <typename T, typename Compare>
void quickSort(Array<T>& values, Compare compare) {
    ordenar(values, std::move(compare));
}

template <typename T>
void quickSort(Array<T>& values) {
    ordenar(values);
}
