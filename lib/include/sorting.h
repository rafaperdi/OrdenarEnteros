#pragma once

#include "array.h"
#include <functional>

// Función de ordenamiento genérica con comparador por defecto
template <typename T>
void ordenar(Array<T>& arreglo) {
    int n = arreglo.size();
    for (int i = 0; i < n - 1; ++i) {
        int minimo = i;
        for (int j = i + 1; j < n; ++j) {
            if (arreglo[j] < arreglo[minimo]) {
                minimo = j;
            }
        }
        if (minimo != i) {
            T temp = arreglo[i];
            arreglo[i] = arreglo[minimo];
            arreglo[minimo] = temp;
        }
    }
}

// Función de ordenamiento genérica con comparador customizado
template <typename T, typename Comparador>
void ordenar(Array<T>& arreglo, Comparador comp) {
    int n = arreglo.size();
    for (int i = 0; i < n - 1; ++i) {
        int minimo = i;
        for (int j = i + 1; j < n; ++j) {
            if (comp(arreglo[j], arreglo[minimo])) {
                minimo = j;
            }
        }
        if (minimo != i) {
            T temp = arreglo[i];
            arreglo[i] = arreglo[minimo];
            arreglo[minimo] = temp;
        }
    }
}

// Versión de ordenamiento rápido (quicksort)
template <typename T>
void quickSort(Array<T>& arreglo, int izquierda = 0, int derecha = -1) {
    if (derecha == -1) {
        derecha = arreglo.size() - 1;
    }
    
    if (izquierda < derecha) {
        int pi = particion(arreglo, izquierda, derecha);
        quickSort(arreglo, izquierda, pi - 1);
        quickSort(arreglo, pi + 1, derecha);
    }
}

// Función auxiliar para quicksort
template <typename T>
int particion(Array<T>& arreglo, int izquierda, int derecha) {
    T pivote = arreglo[derecha];
    int i = izquierda - 1;
    
    for (int j = izquierda; j < derecha; ++j) {
        if (arreglo[j] < pivote) {
            ++i;
            T temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
        }
    }
    
    T temp = arreglo[i + 1];
    arreglo[i + 1] = arreglo[derecha];
    arreglo[derecha] = temp;
    
    return i + 1;
}
