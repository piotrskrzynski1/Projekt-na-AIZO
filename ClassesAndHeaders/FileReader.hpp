#pragma once
#include <fstream>
#include <iostream>
#include "Timer.h"
#include "Utilities.hpp"

class FileReader {
public:
    static int CountLinesInFile(const char* nazwa_pliku) {
        std::ifstream plik(nazwa_pliku);

        if (!plik.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku! Error FileReader::SprawdzIloscLinii()" << std::endl;
            return 0;
        }

        const int max_length = 256;
        char linia[max_length];
        int liczba_linii = 0;


        // Czytamy plik linia po linii i liczymy linie
        while (plik.getline(linia, max_length)) {
            liczba_linii++;
        }

        // Zamykamy plik
        plik.close();

        return liczba_linii;
    }
    template<typename t>
    static t* BuildArrayFromFile(const char* nazwa_pliku,size_t& size) {
        int liczba_linii = CountLinesInFile(nazwa_pliku);
        if (liczba_linii == 0) {
            std::cerr << "Brak linii w pliku! Error FileReader::ZbudujTabliceZPliku()" << std::endl;
            return nullptr;
        }

        std::ifstream plik(nazwa_pliku);
        if (!plik.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku! Error FileReader::ZbudujTabliceZPliku()" << std::endl;
            return nullptr;
        }

        t* tablica = Utilities::createArray<t>(liczba_linii);
        for (int i = 0; i < liczba_linii; i++) {
            plik >> tablica[i];  // Direct read instead of getline+cast
        }
        plik.close();
        size = liczba_linii;
        return tablica;
    }

    template<typename t>
    static void SaveArrayToFile(t* tablica,size_t dlugosc_tablicy, const char* nazwa_pliku) {
        std::ofstream plik(nazwa_pliku);
        if (!plik.is_open()) {
            std::cerr << "Nie mozna zapisać pliku! Error FileReader::ZapiszTabliceDoPliku()" << std::endl;
            return;
        }
        for (int i = 0; i < dlugosc_tablicy;i++) {
            plik << tablica[i] << std::endl;
        }
        plik.close();
    }
    template<typename t>
    static void SaveArrayToFile(t* tablica,size_t dlugosc_tablicy, const char* nazwa_pliku,Timer* timer) {
        std::ofstream plik(nazwa_pliku);
        if (!plik.is_open()) {
            std::cerr << "Nie mozna zapisać pliku! Error FileReader::ZapiszTabliceDoPliku()" << std::endl;
        }
        for (int i = 0; i < dlugosc_tablicy;i++) {
            plik << tablica[i] << std::endl;
        }
        plik << "Czas sortowania:" << timer->result() << std::endl;
        plik.close();
    }

};



