#pragma once
#include "Timer.h"
#include "Game.hpp"
#include <functional>

class SortingAlgorithms {
public:
    template<typename T>
    static void BubbleSort(T* array, size_t size, Timer* timer) {
        timer->start();
        for (size_t i = 0; i < size-1; i++) {
            for (size_t j = 0; j < size-i-1; j++) {
                if (array[j] > array[j+1]) {
                    T temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
        timer->stop();
    }

    template<typename T>
    static void MergeSort(T* array, size_t size, Timer* timer) {
        timer->start();
        auto merge = [&](int l, int m, int r) {
            int n1 = m - l + 1;
            int n2 = r - m;
            T* L = new T[n1];
            T* R = new T[n2];
            for (int i = 0; i < n1; i++)
                L[i] = array[l + i];
            for (int j = 0; j < n2; j++)
                R[j] = array[m + 1 + j];
            int i = 0, j = 0, k = l;
            while (i < n1 && j < n2) {
                if (L[i] <= R[j])
                    array[k++] = L[i++];
                else
                    array[k++] = R[j++];
            }
            while (i < n1)
                array[k++] = L[i++];
            while (j < n2)
                array[k++] = R[j++];
            delete[] L;
            delete[] R;
        };
        std::function<void(int, int)> mergeSort = [&](int l, int r) {
            if (l < r) {
                int m = l + (r - l) / 2;
                mergeSort(l, m);
                mergeSort(m + 1, r);
                merge(l, m, r);
            }
        };
        mergeSort(0, static_cast<int>(size) - 1);
        timer->stop();
    }

    template<typename T>
    static void InsertionSort(T* array, size_t size, Timer* timer) {
        timer->start();
        for (size_t i = 1; i < size; i++) {
            T key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
        timer->stop();
    }

    template<typename T>
    static void BinaryInsertionSort(T* array, size_t size, Timer* timer) {
        timer->start();
        for (size_t i = 1; i < size; i++) {
            T key = array[i];
            int left = 0, right = i - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (key < array[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            for (int j = i - 1; j >= left; j--)
                array[j + 1] = array[j];
            array[left] = key;
        }
        timer->stop();
    }

    template<typename T>
    static void HeapSort(T* array, size_t size, Timer* timer) {
        timer->start();
        auto heapify = [&](int n, int i, auto& heapify_ref) -> void {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            if (l < n && array[l] > array[largest])
                largest = l;
            if (r < n && array[r] > array[largest])
                largest = r;
            if (largest != i) {
                T temp = array[i];
                array[i] = array[largest];
                array[largest] = temp;
                heapify_ref(n, largest, heapify_ref);
            }
        };
        for (int i = static_cast<int>(size) / 2 - 1; i >= 0; i--)
            heapify(static_cast<int>(size), i, heapify);
        for (int i = static_cast<int>(size) - 1; i > 0; i--) {
            T temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            heapify(i, 0, heapify);
        }
        timer->stop();
    }

    template <typename T>
static void QuickSortHelper(T* array, int low, int high) {
        if (low < high) {
            T pivot = array[high];
            int i = low - 1;

            for (int j = low; j < high; j++) {
                if (array[j] < pivot) {
                    i++;
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }

            T temp = array[i + 1];
            array[i + 1] = array[high];
            array[high] = temp;
            int pi = i + 1;

            QuickSortHelper(array, low, pi - 1);
            QuickSortHelper(array, pi + 1, high);
        }
    }

    template <typename T>
    static void QuickSort(T* array, const size_t size, Timer* timer) {
        timer->start();
        QuickSortHelper(array, 0, static_cast<int>(size) - 1);
        timer->stop();
    }

    template<typename T>
    static void ShellSort(T* array, size_t size, Timer* timer) {
        timer->start();
        for (int gap = static_cast<int>(size) / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < static_cast<int>(size); i++) {
                T temp = array[i];
                int j;
                for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                    array[j] = array[j - gap];
                array[j] = temp;
            }
        }
        timer->stop();
    }

    template<typename T>
    static void bubble_sort_pijany(T* arr, size_t size, float pijanstwo) {
        // Run the beer game and get the efficiency percentage.
        int objectsToSpawn = std::max(30, static_cast<int>(size%56));
        float efficiency = Game::startBeerGame(objectsToSpawn, pijanstwo);
        int percent = static_cast<int>(efficiency);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dice(1, 12);
        int rzut = dice(gen);

        if (rzut >= 11) {
            // Full sorting.
            for (size_t i = 0; i < size - 1; ++i) {
                for (size_t j = 0; j < size - i - 1; ++j) {
                    if (arr[j] > arr[j + 1])
                        std::swap(arr[j], arr[j + 1]);
                }
            }
        } else {
            // Partial sorting based on efficiency, with added randomness.
            int limit = (size * percent) / 100;

            /* Introduce random variation up to 25% of the size.
            std::uniform_int_distribution<> varDist(0, size / 4);
            int variation = varDist(gen);

            // Calculate the new limit with variation.
            int limit = baseLimit + variation;

            // Ensure that the limit stays within valid bounds.
            if (limit < 1) {
                limit = 1;  // Minimum limit is 1 (at least one element should be sorted).
            }
            if (limit > static_cast<int>(size)) {
                limit = size;  // Maximum limit should be the size of the array.
            }*/

            // Perform bubble sort only on the first `limit` elements.
            for (int i = 0; i < limit - 1; ++i) {
                for (int j = 0; j < limit - i - 1; ++j) {
                    if (arr[j] > arr[j + 1])
                        std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }


};
