#pragma once

#include <initializer_list>
#include <vector>
#include <iostream>

template <typename T>
class Array {
public:
    Array(std::initializer_list<T> valores);

    size_t size() const noexcept;
    T& operator[](size_t indice);
    const T& operator[](size_t indice) const;
    void print() const;

private:
    std::vector<T> datos_;
};

// Implementación inline de Array template

template <typename T>
Array<T>::Array(std::initializer_list<T> valores) : datos_(valores) {}

template <typename T>
size_t Array<T>::size() const noexcept {
    return datos_.size();
}

template <typename T>
T& Array<T>::operator[](size_t indice) {
    return datos_[indice];
}

template <typename T>
const T& Array<T>::operator[](size_t indice) const {
    return datos_[indice];
}

template <typename T>
void Array<T>::print() const {
    std::cout << "[";
    for (size_t i = 0; i < datos_.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << datos_[i];
    }
    std::cout << "]" << std::endl;
}
