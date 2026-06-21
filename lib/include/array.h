#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

template <typename T>
class Array {
public:
    using value_type = T;
    using size_type = typename std::vector<T>::size_type;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    Array() = default;
    Array(std::initializer_list<T> values) : data_(values) {}
    explicit Array(std::vector<T> values) : data_(std::move(values)) {}

    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    [[nodiscard]] size_type size() const noexcept {
        return data_.size();
    }

    T& operator[](size_type index) noexcept {
        return data_[index];
    }

    const T& operator[](size_type index) const noexcept {
        return data_[index];
    }

    T& at(size_type index) {
        return data_.at(index);
    }

    const T& at(size_type index) const {
        return data_.at(index);
    }

    iterator begin() noexcept {
        return data_.begin();
    }

    const_iterator begin() const noexcept {
        return data_.begin();
    }

    const_iterator cbegin() const noexcept {
        return data_.cbegin();
    }

    iterator end() noexcept {
        return data_.end();
    }

    const_iterator end() const noexcept {
        return data_.end();
    }

    const_iterator cend() const noexcept {
        return data_.cend();
    }

    T* data() noexcept {
        return data_.data();
    }

    const T* data() const noexcept {
        return data_.data();
    }

    void print(std::ostream& output = std::cout) const {
        output << '[';
        for(size_type index = 0; index < data_.size(); ++index) {
            if(index != 0) {
                output << ", ";
            }
            output << data_[index];
        }
        output << "]\n";
    }

private:
    std::vector<T> data_;
};
