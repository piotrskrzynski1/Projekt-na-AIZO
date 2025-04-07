#pragma once
#include <iostream>
#include <random>
#include <limits>
#include <cstring>
#include "Vector.hpp"
#include "Planszowka.hpp"

class Utilities {
public:
    static constexpr const char* help = R"(Pomoc dla uzytkownika!

[wywolanie programu]:
tutaj po prostu wpisujemy sciezke .../projektaizo.exe (PRZYKLAD)
[tryb]
Syntax = [wywolanie programu] [tryb] [algorytm] [typ danych] [ilosc wywolan] [rozmiar tablic]
--plik: tryb w ktorym wykonywany jest odczyt z i zapis do pliku. jedyny wazny argument to [algorytm] i [typ danych], reszte wypelnic zerami
--benchmark: tryb dowolnego pomiaru. liczy sie kazdy parametr. podstawowy test wedlug wybranych ustawien
--badanie1: wykonuje badanie 1 z projektu, badamy wplyw rozmiaru tablic. Kazdy parametr jest potrzebny oprocz [rozmiar tablic]
--badanie2: wykonuje badanie 2 z projektu, badamy wplyw wstepnego uporzadkowania tablicy. Kazdy parametr jest potrzebny
--badanie3: wykonuje badanie 3 z projektu, badamy wybrany algorytm i wplyw kazdego typu danych na jego predkosc obliczeniowa. Kazdy parametr oprocz [typ danych] potrzebny. Typ danych ustawic na dowolna wartosc
--test: sprawdza wszystko

Syntax = [wywolanie programu] [tryb] [typ danych] [ilosc wywolan] [rozmiar tablic] [poziom pijanstwa]
--pijany: wykonuje algorytm bubblesort i uzywa symulacji pijanego studenta ktory musi wypic kazda krople piwa ktora poleci do jego buzki. Im wiekszy poziom pijanstwa(0.0-1.0) tym gorzej bedzie sobie z tym radzil.
przy badaniach liczy sie tylko [algorytm] i [typ danych] reszte wypelnic zerami
--pijanybadanie1: wykonuje pijane badanie 1 z projektu, badamy wplyw rozmiaru tablic na błędy w pijackim bubble sorcie. Kazdy parametr jest potrzebny oprocz [rozmiar tablic]
--pijanybadanie2: wykonuje pijane badanie 2 z projektu, badamy wplyw na błąd wstepnego uporzadkowania tablicy na pijackim bubblesorcie. Kazdy parametr jest potrzebny
--pijanybadanie3: wykonuje piajne badanie 3 z projektu, badamy pijacki bubble sort i wplyw kazdego typu danych na jego błedy. Kazdy parametr oprocz [typ danych] potrzebny. Typ danych ustawic na dowolna wartosc
[Algorytm]:
0-BUBBLESORT, 1-QUICKSORT, 2-MERGESORT, 3-INSERTIONSORT,
4-BINARY INSERTIONSORT, 5-SHELL SORT, 6-HEAPSORT
[typ danych]:
0 - INT, 1 - FLOAT, 2 - DOUBLE, 3 - CHAR, 4 - PLANSZOWKA
[ilosc wywolan]:
ile testow mamy wykonac?
od 0 do tyle ile pozwala trzymac INTEGER na twoim systemie
[rozmiar tablic]:
od 0 do tyle ile pozwala trzymac INTEGER na twoim systemie

PROSZE NIE PRZESADZAC Z USTAWIANIEM ARGUMENTOW I UZYWAC LOGIKI BO NIE DODALEM SPRAWDZANIA ARGUMENTOW (lenistwo?)
)";

    template <typename T>
    static T* createArray(int rozmiar_tablicy) {
        return new T[rozmiar_tablicy];
    }

    static void cleanUpArray(void* tablica, const int arg2) {
        if (tablica != nullptr) {
            switch (arg2) {
                case 0: delete[] static_cast<int*>(tablica); break;
                case 1: delete[] static_cast<float*>(tablica); break;
                case 2: delete[] static_cast<double*>(tablica); break;
                case 3: delete[] static_cast<char*>(tablica); break;
                default:
                    std::cerr << "Nieznajomy typ danych tablicy przy usuwaniu!" << std::endl;
                    break;
            }
        }
    }

    template <typename T>
    static int checkIfSortedArray(T* tablica, const int rozmiar_tablicy) {
        if (rozmiar_tablicy < 2)
            throw std::invalid_argument("Zły rozmiar tablicy w template Utilities::checkArray");
        for (int i = 1; i < rozmiar_tablicy; i++) {
            if (tablica[i] < tablica[i - 1])
                return 0;
        }
        return 1;
    }

    template <typename T>
    static float checkPercentageSorted(T* tablica, const int rozmiar_tablicy) {
        if (rozmiar_tablicy < 2)
            throw std::invalid_argument("Bad array size in Utilities::checkArray");

        int disorderCount = 0;
        for (int i = 1; i < rozmiar_tablicy; ++i) {
            if (tablica[i] < tablica[i - 1])
                disorderCount++;
        }

        float disorderRatio = static_cast<float>(disorderCount) / (rozmiar_tablicy - 1);
        float sortedRatio = 1.0f - disorderRatio;

        std::cout << "\nDisorder: " << disorderCount
                  << "\nTotal comparisons: " << (rozmiar_tablicy - 1)
                  << "\nSortedness: " << (sortedRatio * 100.0f) << "%\n";

        return sortedRatio;
    }

    // Generic template for filling an array with random numbers.
    template <typename T>
    static void fillArrayWithRandomNumbers(T* array, int size) {
        // Random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        if (typeid(T) == typeid(int)) {
            std::uniform_int_distribution<int> dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            for (int i = 0; i < size; i++) {
                array[i] = dis(gen);
            }
        }
        else if (typeid(T) == typeid(float)) {
            std::uniform_real_distribution<float> dis(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
            for (int i = 0; i < size; i++) {
                array[i] = dis(gen);
            }
        }
        else if (typeid(T) == typeid(double)) {
            std::uniform_real_distribution<double> dis(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
            for (int i = 0; i < size; i++) {
                array[i] = dis(gen);
            }
        }
        else if (typeid(T) == typeid(char)) {
            std::uniform_int_distribution<int> dis(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
            for (int i = 0; i < size; i++) {
                array[i] = static_cast<char>(dis(gen));
            }
        }
    }

    // Calculate the median from a Vector of size_t.
    static size_t CalculateMedian(Vector<size_t> &medianList) {
        size_t median;
        if (medianList.size() % 2 == 1) {
            median = medianList[medianList.size() / 2];
        } else {
            const size_t mid1 = medianList[medianList.size() / 2 - 1];
            const size_t mid2 = medianList[medianList.size() / 2];
            median = (mid1 + mid2) / 2;
        }
        return median;
    }
};

// ---
// Now, outside the class definition (in the global scope),
// we provide the explicit specialization of fillArrayWithRandomNumbers for Planszowka.
template <>
inline void Utilities::fillArrayWithRandomNumbers<Planszowka>(Planszowka* array, int size) {
    for (int i = 0; i < size; i++) {
        // Generate valid random parameters within the correct ranges.
        int minGraczy = rand() % 10 + 1; // [1,10]
        int maxGraczy = minGraczy + rand() % (11 - minGraczy); // ensuring min <= max <= 10
        int czas = rand() % (480 - 5 + 1) + 5; // [5,480]
        int skomplikowanie = rand() % 10 + 1; // [1,10]
        int radosc = rand() % 10 + 1; // [1,10]
        // Fixed valid strings for simplicity.
        const char* nazwa = "GameName";
        const char* wydawca = "Publisher";

        try {
            array[i] = Planszowka(nazwa, wydawca, minGraczy, maxGraczy, czas, skomplikowanie, radosc);
        }
        catch (const std::exception& e) {
            std::cerr << "Error creating Planszowka: " << e.what() << "\n";
        }
    }
}
