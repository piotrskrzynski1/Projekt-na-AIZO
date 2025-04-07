#pragma once
#include "Timer.h"
#include "SortingAlgorithms.hpp"
class TestsUtilities {
public:
    // Sortowanie rosnąco (pełne)
    template <typename T>
    static void sortAscending(T* array, size_t size, Timer* timer, const float LEAVEDEFAULT = 1.0f) {
        SortingAlgorithms::QuickSort(array, size, timer);
    }


    template <typename T>
    static void sortDescending(T* array, size_t size, Timer* timer, const float LEAVEDEFAULT = 1.0f) {
        SortingAlgorithms::QuickSort(array, size, timer);

        for (size_t i = 0; i < size / 2; i++) {
            T temp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = temp;
        }
    }

    template <typename T>
    static void partialSortAscending(T* array, const size_t size, Timer* timer,const float fraction) {
        if (fraction < 0.0f || fraction > 1.0f) {
            throw std::invalid_argument("Fraction must be between 0 and 1");
        }

        size_t count = static_cast<size_t>(size * fraction);
        if (count < 2) return;

        SortingAlgorithms::QuickSort(array, count, timer);
    }

    template <typename T>
    static void partialSortDescending(T* array, const size_t size, Timer* timer, const float fraction) {
        if (fraction < 0.0f || fraction > 1.0f) {
            throw std::invalid_argument("Fraction must be between 0 and 1");
        }

        size_t count = static_cast<size_t>(size * fraction);
        if (count < 2) return;

        SortingAlgorithms::QuickSort(array, count, timer);
    }
};