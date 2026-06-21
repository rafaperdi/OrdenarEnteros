#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <vector>

template <typename T>
class Array {
public:
    Array(std::initializer_list<T> valores);

    std::size_t size() const noexcept;
    T& operator[](std::size_t indice);
    const T& operator[](std::size_t indice) const;
    void print() const;

private:
    std::vector<T> datos_;
};

// Implementación inline de Array template

template <typename T>
Array<T>::Array(std::initializer_list<T> valores) : datos_(valores) {}

template <typename T>
std::size_t Array<T>::size() const noexcept {
    return datos_.size();
}

template <typename T>
T& Array<T>::operator[](std::size_t indice) {
    return datos_[indice];
}

template <typename T>
const T& Array<T>::operator[](std::size_t indice) const {
    return datos_[indice];
}

template <typename T>
void Array<T>::print() const {
    std::cout << "[";
    for (std::size_t i = 0; i < datos_.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << datos_[i];
    }
    std::cout << "]" << std::endl;
}
