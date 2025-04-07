#pragma once
#include <unordered_map>

#include "ArgumentHolder.h"
#include "SortingAlgorithms.hpp"
#include "Utilities.hpp"
#include "TestsUtilities.hpp"
#include "Timer.h"
#include "Planszowka.hpp"
#include <iostream>
#include <fstream>

#define PLAY_MP3 "start pijak.mp3"

//DODAC JAK DODAJESZ NOWE TYPY DANYCH TODO
template<typename T>
inline std::unordered_map<int, void (*)(T*,size_t,Timer*)> Algorytmy = {
    {0, SortingAlgorithms::BubbleSort},
    {1, SortingAlgorithms::QuickSort},
    {2, SortingAlgorithms::MergeSort},
    {3, SortingAlgorithms::InsertionSort},
    {4, SortingAlgorithms::BinaryInsertionSort},
    {5, SortingAlgorithms::ShellSort},
    {6, SortingAlgorithms::HeapSort},
};
template<typename T>
inline std::unordered_map<int, void (*)(T*,size_t,Timer*,float)> Algorytmy_Test_Utilities = {
    {0, TestsUtilities::sortAscending},
    {1, TestsUtilities::sortDescending},
    {2, TestsUtilities::partialSortAscending},
    {3, TestsUtilities::partialSortDescending}
};

inline std::unordered_map<int,const char*> Typy_Danych = {
    {0,"Integer"},
    {1, "Float"},
    {2,"Double"},
    {3,"Char"},
    {4, "Planszowka"}
};

inline std::unordered_map<int,const char*> Algorytmy_Nazwy = {
    {0, "BUBBLE SORT"},
    {1, "QUICK SORT"},
    {2, "MERGE SORT"},
    {3, "INSERTION SORT"},
    {4, "BINARY INSERTION SORT"},
    {5, "SHELL SORT"},
    {6, "HEAP SORT"},
};


class Tests {
public:
    static std::fstream fs;

    template<typename T>
    static void ProcessArrayBenchmark(ArgumentHolder* args, Timer* timer) {

        OpenFile();
        const size_t size = args->GetChosenArraySize();
        const int iterations = args->GetChosenIterationAmount();
        Vector<size_t> medianList;
        long long srednia = 0;

        T* array = Utilities::createArray<T>(size);


        for (int i = 0; i < iterations; i++) {
            Utilities::fillArrayWithRandomNumbers(array, size);
            Algorytmy<T>[args->GetChosenAlgorithm()](array,size,timer);
            std::cout << "got in " << args->GetChosenDataType() << std::endl;
            srednia += timer->result();
            medianList.push_back(timer->result());
            if (args->GetProgramMode()=="--test") {
                if (Utilities::checkIfSortedArray(array, size)) {
                    WriteToFile("CORRECTLY SORTED\n");  // Green text
                } else {
                    WriteToFile("✖ !!!!!NOT SORTED CORRECTLY!!!!!");  // Red text
                    throw std::bad_exception();
                }
            }
            timer->reset();
        }

        srednia /= iterations;

        WriteToFile("Wywolania: " + std::to_string(iterations));
        WriteToFile("Rozmiar tablic: " + std::to_string(args->GetChosenArraySize()));
        WriteToFile("Typ danych: " + std::string(Typy_Danych.at(args->GetChosenDataType())));
        WriteToFile("Uzyty algorytm: " + std::string(Algorytmy_Nazwy.at(args->GetChosenAlgorithm())));
        WriteToFile("Srednia czasu wykonywania: " + std::to_string(srednia) + " ms");
        WriteToFile("Min: " + std::to_string(medianList.min()) + " ms " + "Max: " + std::to_string(medianList.max()) + " ms ");
        medianList.sort(); //zeby wybrac mediane musi byc posortowany zbiór wyników
        WriteToFile("Mediana czasu wykonywania: " + std::to_string(Utilities::CalculateMedian(medianList)) + " ms\n");

        delete[] array;
    }
    template<typename T>
    static void ProcessPijany(ArgumentHolder* args, Timer* timer) {
        std::system(PLAY_MP3);

        OpenFile();

        Vector<float> procentposortowanych;
        Vector<size_t> medianList;
        long long srednia = 0;
        const size_t size = args->GetChosenArraySize();
        const int iterations = args->GetChosenIterationAmount();

        T* array = Utilities::createArray<T>(size);

        for (int i = 0; i < iterations; i++) {
            Utilities::fillArrayWithRandomNumbers(array, size);
            SortingAlgorithms::bubble_sort_pijany(array,size,args->GetDrunkLevel());
            srednia += timer->result();
            medianList.push_back(timer->result());
            procentposortowanych.push_back(Utilities::checkPercentageSorted(array,size));
            timer->reset();
        }

        srednia /= iterations;
        if(args->GetDrunkLevel() <= 0.2){
            WriteToFile("Jak tam chlopie dawaj tu w alkomat dmuchaj: " + std::to_string(args->GetDrunkLevel()) + " (gdzie MIN 0.0-1.0 MAX)");
            WriteToFile("Przynajmniej sortowales w miare trzezwy...albo wciagales powietrze\n");
        }else {
            WriteToFile("Jak tam chlopie dawaj tu w alkomat dmuchaj: " + std::to_string(args->GetDrunkLevel()) + " (gdzie MIN 0.0-1.0 MAX)");
            WriteToFile("Ty par##ywy pijaku! Miales posortowac liczby, a nie piwo w swoim brzuchu!");
        }
        WriteToFile("Wywolania: " + std::to_string(iterations));
        WriteToFile("Rozmiar tablic: " + std::to_string(args->GetChosenArraySize()));
        WriteToFile("Typ danych: " + std::string(Typy_Danych.at(args->GetChosenDataType())));
        WriteToFile("Uzyty algorytm: " + std::string(Algorytmy_Nazwy.at(args->GetChosenAlgorithm())));
        WriteToFile("Srednia czasu wykonywania: " + std::to_string(srednia) + " ms");
        WriteToFile("Min: " + std::to_string(medianList.min()) + " ms " + "Max: " + std::to_string(medianList.max()) + " ms ");
        medianList.sort(); //zeby wybrac mediane musi byc posortowany zbiór wyników
        WriteToFile("Mediana czasu wykonywania: " + std::to_string(Utilities::CalculateMedian(medianList)) + " ms\n");

        std::string sortAccuracies;

        for (int i = 0; i < procentposortowanych.size(); ++i) {
            sortAccuracies += std::to_string(procentposortowanych[i]*100) + ", ";
        }
        WriteToFile("% dokladnosci kazdego sortu: " + std::string(sortAccuracies) + "\n");
        delete[] array;
    }
    template<typename T>
    static void ProcessArrayFile(ArgumentHolder* args, Timer* timer) {
        OpenFile();
        size_t size;
        T* array = FileReader::BuildArrayFromFile<T>("input.txt",size);
        Algorytmy<T>[args->GetChosenAlgorithm()](array,size,timer);
        int sortingresult = Utilities::checkIfSortedArray(array,size);
        (sortingresult == 1) ? std::cout << "Sortowanie pomyslne" << std::endl : std ::cout << "Sortowanie niepomyslne" << std::endl;
        FileReader::SaveArrayToFile(array, size, "output.txt", timer);
        Utilities::cleanUpArray(array, args->GetChosenDataType());
        delete[] array;
    }
protected:
    /*
     *variation
     *-1 = losowe liczby bez porzadku
     *0 = uporzadkowane rosnąco liczby
     *1 = uporządkowane malejąco liczby
     *2 = uporządkowane częsciowo rosnąco liczby
     *3 = uporządkowane częściowo malejąco liczby
     */
    template<typename T>
        static void ProcessArrayStudyTwo(ArgumentHolder* args, Timer* timer,int variation,float partialsorting) {
        OpenFile();
        if (partialsorting < 0.0f || partialsorting > 1.0f) {throw std::invalid_argument("partialsorting musi być 0.0f-1.0f");}
        const size_t size = args->GetChosenArraySize();
        const int iterations = args->GetChosenIterationAmount();
        Vector<size_t> medianList;
        long long srednia = 0;

        T* array = Utilities::createArray<T>(size);

        for (int i = 0; i < iterations; i++) {
            Utilities::fillArrayWithRandomNumbers(array, size);
            //-1 to zwyczajny sort wiec nie chcemy zadnej funkcji do tego.
            if (variation != -1) {
                Algorytmy_Test_Utilities<T>[variation](array,size,timer,partialsorting);
            }
            Algorytmy<T>[args->GetChosenAlgorithm()](array,size,timer);
            srednia += timer->result();
            medianList.push_back(timer->result());
            timer->reset();
        }

        srednia /= iterations;

        WriteToFile("Wywolania: " + std::to_string(iterations));
        WriteToFile("Rozmiar tablic: " + std::to_string(args->GetChosenArraySize()));
        WriteToFile("Typ danych: " + std::string(Typy_Danych.at(args->GetChosenDataType())));
        WriteToFile("Dane byly: ");
        switch (variation) {
            case -1: WriteToFile("nieposortowane,losowe liczby"); break;
            case 0: WriteToFile("posortowane rosnaco na start");break;
            case 1: WriteToFile("posortowane malejaco na start");break;
            case 2: WriteToFile("posortowane czesciowo rosnaco w " + std::to_string(partialsorting*10) + "%");break;
            case 3: WriteToFile("posortowane czesciowo malejaco w " + std::to_string(partialsorting*10) + "%");break;
            default: WriteToFile("cos poszlo nie tak w ProcessArrayStudyTwo()...koncze test...");return;
        }
        WriteToFile("Uzyty algorytm: " + std::string(Algorytmy_Nazwy.at(args->GetChosenAlgorithm())));
        WriteToFile("Srednia czasu wykonywania: " + std::to_string(srednia) + " ms");
        WriteToFile("Min: " + std::to_string(medianList.min()) + " ms " + "Max: " + std::to_string(medianList.max()) + " ms ");

        medianList.sort(); //zeby wybrac mediane musi byc posortowany zbiór wyników
        WriteToFile("Mediana czasu wykonywania: " + std::to_string(Utilities::CalculateMedian(medianList)) + " ms\n");

        delete[] array;
    }
    template<typename T>
    static void ProcessArrayStudyTwoPijany(ArgumentHolder* args, Timer* timer,int variation,float partialsorting) {
        OpenFile();
        std::system(PLAY_MP3);
        if (partialsorting < 0.0f || partialsorting > 1.0f) {throw std::invalid_argument("partialsorting musi być 0.0f-1.0f");}
        const size_t size = args->GetChosenArraySize();
        const int iterations = args->GetChosenIterationAmount();
        Vector<size_t> medianList;
        long long srednia = 0;

        T* array = Utilities::createArray<T>(size);

        for (int i = 0; i < iterations; i++) {
            Utilities::fillArrayWithRandomNumbers(array, size);
            //-1 to zwyczajny sort wiec nie chcemy zadnej funkcji do tego.
            if (variation != -1) {
                Algorytmy_Test_Utilities<T>[variation](array,size,timer,partialsorting);
            }
            SortingAlgorithms::bubble_sort_pijany(array,size,args->GetDrunkLevel());
            srednia += timer->result();
            medianList.push_back(timer->result());
            timer->reset();
        }

        srednia /= iterations;

        WriteToFile("Wywolania: " + std::to_string(iterations));
        WriteToFile("Rozmiar tablic: " + std::to_string(args->GetChosenArraySize()));
        WriteToFile("Typ danych: " + std::string(Typy_Danych.at(args->GetChosenDataType())));
        WriteToFile("Dane byly: ");
        switch (variation) {
            case -1: WriteToFile("nieposortowane,losowe liczby"); break;
            case 0: WriteToFile("posortowane rosnaco na start");break;
            case 1: WriteToFile("posortowane malejaco na start");break;
            case 2: WriteToFile("posortowane czesciowo rosnaco w " + std::to_string(partialsorting*10) + "%");break;
            case 3: WriteToFile("posortowane czesciowo malejaco w " + std::to_string(partialsorting*10) + "%");break;
            default: WriteToFile("cos poszlo nie tak w ProcessArrayStudyTwo()...koncze test...");return;
        }
        WriteToFile("Uzyty algorytm: " + std::string(Algorytmy_Nazwy.at(args->GetChosenAlgorithm())));
        WriteToFile("Srednia czasu wykonywania: " + std::to_string(srednia) + " ms");
        WriteToFile("Min: " + std::to_string(medianList.min()) + " ms " + "Max: " + std::to_string(medianList.max()) + " ms ");

        medianList.sort(); //zeby wybrac mediane musi byc posortowany zbiór wyników
        WriteToFile("Mediana czasu wykonywania: " + std::to_string(Utilities::CalculateMedian(medianList)) + " ms\n");

        delete[] array;
    }
public:
    template<typename T>
    static void StudyOneDatasetSize(ArgumentHolder* args, Timer* timer) {
        int datasetSizes[] = {10000, 20000, 40000, 80000, 160000};
        const int og_size = args->GetChosenArraySize();
        for (const int size : datasetSizes) {
            args->SetChosenArraySize(size);
            std::cout << "Badanie dla rozmiaru: " << size << std::endl;
            ProcessArrayBenchmark<T>(args, timer);
        }
        args->SetChosenArraySize(og_size);
    }

    template<typename T>
    static void StudyTwoInitialDistribution(ArgumentHolder* args, Timer* timer) {
        OpenFile();
        float partialSorting = 0.33f;
        ProcessArrayStudyTwo<T>(args, timer, 0,1.0f);
        ProcessArrayStudyTwo<T>(args, timer, 1,1.0f);
        ProcessArrayStudyTwo<T>(args, timer, 2,partialSorting);
        ProcessArrayStudyTwo<T>(args, timer, 3,partialSorting);
        partialSorting = 0.66f;
        ProcessArrayStudyTwo<T>(args, timer, 2,partialSorting);
        ProcessArrayStudyTwo<T>(args, timer, 3,partialSorting);
    }

    static void StudyThreeDataTypeImpact(ArgumentHolder* args, Timer* timer) {
        int originaldatatype = args->GetChosenDataType();
        args->SetChosenDataType(0);
        ProcessArrayBenchmark<int>(args, timer);
        args->SetChosenDataType(1);
        ProcessArrayBenchmark<float>(args, timer);
        args->SetChosenDataType(2);
        ProcessArrayBenchmark<double>(args, timer);
        args->SetChosenDataType(3);
        ProcessArrayBenchmark<char>(args, timer);
        args->SetChosenDataType(4);
        ProcessArrayBenchmark<Planszowka>(args,timer);
        args->SetChosenDataType(originaldatatype);
    }
    template<typename T>
    static void StudyOneDataSizePijany(ArgumentHolder* args, Timer* timer){
        OpenFile();
        int dataSizes[] = {10000,20000,40000,80000,160000};
        const int og_size = args->GetChosenArraySize();
        for (const int size : dataSizes) {
            args->SetChosenArraySize(size);
            std::cout << "Badanie dla rozmiaru: " << size << std::endl;
            ProcessPijany<T>(args, timer);
        }
        args->SetChosenArraySize(og_size);
    }

    template<typename T>
    static void StudyTwoInitialDistributionPijany(ArgumentHolder* args, Timer* timer) {
        OpenFile();
        float partialSorting = 0.33f;
        ProcessArrayStudyTwoPijany<T>(args, timer, 0,1.0f);
        ProcessArrayStudyTwoPijany<T>(args, timer, 1,1.0f);
        ProcessArrayStudyTwoPijany<T>(args, timer, 2,partialSorting);
        ProcessArrayStudyTwoPijany<T>(args, timer, 3,partialSorting);
        partialSorting = 0.66f;
        ProcessArrayStudyTwoPijany<T>(args, timer, 2,partialSorting);
        ProcessArrayStudyTwoPijany<T>(args, timer, 3,partialSorting);
    }

    static void StudyThreeDataTypeImpactPijany(ArgumentHolder* args, Timer* timer) {
        int originaldatatype = args->GetChosenDataType();
        args->SetChosenDataType(0);
        ProcessPijany<int>(args, timer);
        args->SetChosenDataType(1);
        ProcessPijany<float>(args, timer);
        args->SetChosenDataType(2);
        ProcessPijany<double>(args, timer);
        args->SetChosenDataType(3);
        ProcessPijany<char>(args, timer);
        args->SetChosenDataType(originaldatatype);
    }

    static void OpenFile() {
        if (!fs.is_open()) {
            fs.open("./wyniki.txt", std::fstream::out | std::fstream::trunc);
            if (!fs.is_open()) {
                std::cerr << "Error opening the file!" << std::endl;
            }
        }
    }


    static void CloseFile() {
        if (fs.is_open()) {
            fs.close();
        }
    }


    static void WriteToFile(const std::string& data) {
        if (fs.is_open()) {
            fs << data << std::endl;
        } else {
            std::cerr << "File not open, cannot write!" << std::endl;
        }
    }
};
std::fstream Tests::fs;