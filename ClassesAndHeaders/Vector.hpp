#pragma once
#include <stdexcept>
#include <limits>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t length;

    void resize(const size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < length; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void quicksort(const int left, int right) {
        if (left >= right) return;
        T pivot = data[right];
        int partitionIndex = left;
        for (int i = left; i < right; i++) {
            if (data[i] < pivot) {
                std::swap(data[i], data[partitionIndex]);
                partitionIndex++;
            }
        }
        std::swap(data[partitionIndex], data[right]);
        quicksort(left, partitionIndex - 1);
        quicksort(partitionIndex + 1, right);
    }

public:
    Vector() : data(nullptr), capacity(0), length(0) {}

    ~Vector() { delete[] data; }

    void push_back(const T& value) {
        if (length == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[length++] = value;
    }

    void pop_back() {
        if (length > 0) {
            length--;
        }
    }

    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    [[nodiscard]] size_t size() const { return length; }

    [[nodiscard]] bool empty() const { return length == 0; }

    void sort() {
        if (length > 1) {
            quicksort(0, length - 1);
        }
    }

    // Get the minimum value in the vector
    T min() const {
        if (empty()) {
            throw std::runtime_error("Vector is empty, cannot find minimum");
        }
        T min_value = data[0];
        for (size_t i = 1; i < length; i++) {
            if (data[i] < min_value) {
                min_value = data[i];
            }
        }
        return min_value;
    }

    // Get the maximum value in the vector
    T max() const {
        if (empty()) {
            throw std::runtime_error("Vector is empty, cannot find maximum");
        }
        T max_value = data[0];
        for (size_t i = 1; i < length; i++) {
            if (data[i] > max_value) {
                max_value = data[i];
            }
        }
        return max_value;
    }
};
