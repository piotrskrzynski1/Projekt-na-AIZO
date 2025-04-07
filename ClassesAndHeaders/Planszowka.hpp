#pragma once
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "Vector.hpp"

class Planszowka {
private:
    char* nazwa;       // maks. 25 znaków
    char* wydawca;     // maks. 25 znaków
    int minGraczy;     // zakres 1-10
    int maxGraczy;     // zakres 1-10
    int czas;          // czas rozgrywki w minutach, zakres 5-480
    int skomplikowanie; // zakres 1-10
    int radosc;        // zakres 1-10
    double fajnosc;

public:
    Planszowka(const Planszowka& other)
            : minGraczy(other.minGraczy), maxGraczy(other.maxGraczy),
              czas(other.czas), skomplikowanie(other.skomplikowanie),
              radosc(other.radosc), fajnosc(other.fajnosc) {
        // Allocate memory and copy strings
        nazwa = new char[strlen(other.nazwa) + 1];
        wydawca = new char[strlen(other.wydawca) + 1];
        strcpy(nazwa, other.nazwa);
        strcpy(wydawca, other.wydawca);
    }

    // Default constructor
    Planszowka()
            : nazwa(nullptr), wydawca(nullptr),
              minGraczy(0), maxGraczy(0), czas(0),
              skomplikowanie(0), radosc(0), fajnosc(0.0) {}

    // Parametrized constructor with validation
    Planszowka(const char* nazwa,
               const char* wydawca,
               int minGraczy,
               int maxGraczy,
               int czas,
               int skomplikowanie,
               int radosc)
            : minGraczy(minGraczy), maxGraczy(maxGraczy),
              czas(czas), skomplikowanie(skomplikowanie), radosc(radosc),fajnosc(0.0)
    {
        // Validate inputs
        if (strlen(nazwa) > 25)
            throw std::invalid_argument("Nazwa przekracza 25 znakow.");
        if (strlen(wydawca) > 25)
            throw std::invalid_argument("Wydawca przekracza 25 znakow.");
        if (minGraczy < 1 || minGraczy > 10)
            throw std::invalid_argument("Minimalna liczba graczy poza zakresem 1-10.");
        if (maxGraczy < 1 || maxGraczy > 10)
            throw std::invalid_argument("Maksymalna liczba graczy poza zakresem 1-10.");
        if (minGraczy > maxGraczy)
            throw std::invalid_argument("Minimalna liczba graczy nie moze byc wieksza niz maksymalna.");
        if (czas < 5 || czas > 480)
            throw std::invalid_argument("Czas rozgrywki poza zakresem 5-480 minut.");
        if (skomplikowanie < 1 || skomplikowanie > 10)
            throw std::invalid_argument("Skomplikowanie poza zakresem 1-10.");
        if (radosc < 1 || radosc > 10)
            throw std::invalid_argument("Radosc poza zakresem 1-10.");
        // fajnosc is calculated, so its validation isn't needed from input

        // Dynamically allocate memory for nazwa and wydawca and copy the strings
        this->nazwa = new char[strlen(nazwa) + 1];
        this->wydawca = new char[strlen(wydawca) + 1];

        strcpy(this->nazwa, nazwa);   // Copy string
        strcpy(this->wydawca, wydawca); // Copy string

        // Calculate fajnosc based on the provided parameters
        fajnosc = obliczFajnosc();
    }

    // Destructor to clean up allocated memory
    ~Planszowka() {
        delete[] nazwa;
        delete[] wydawca;
    }

    // Method to calculate "fajność" of the game
    double obliczFajnosc() const {
        double sredniaGraczy = (minGraczy + maxGraczy) / 2.0;
        return (radosc * (11 - skomplikowanie)) / (czas * sredniaGraczy);
    }

    // Getter methods
    const char* getNazwa() const { return nazwa; }
    const char* getWydawca() const { return wydawca; }
    int getMinGraczy() const { return minGraczy; }
    int getMaxGraczy() const { return maxGraczy; }
    int getCzas() const { return czas; }
    int getSkomplikowanie() const { return skomplikowanie; }
    int getRadosc() const { return radosc; }

    // Overloaded comparison operators based on obliczFajnosc()
    friend bool operator<(const Planszowka& lhs, const Planszowka& rhs) {
        return lhs.fajnosc < rhs.fajnosc;
    }

    friend bool operator>(const Planszowka& lhs, const Planszowka& rhs) {
        return lhs.fajnosc > rhs.fajnosc;
    }

    friend bool operator==(const Planszowka& lhs, const Planszowka& rhs) {
        return lhs.fajnosc == rhs.fajnosc;
    }

    friend bool operator<=(const Planszowka& lhs, const Planszowka& rhs) {
        return lhs.fajnosc <= rhs.fajnosc;
    }

    friend bool operator>=(const Planszowka& lhs, const Planszowka& rhs) {
        return lhs.fajnosc >= rhs.fajnosc;
    }

    // Assignment operator overload for Planszowka
    Planszowka& operator=(const Planszowka& rhs) {
        // Check for self-assignment
        if (this == &rhs) {
            return *this;
        }

        // Clean up existing resources
        delete[] nazwa;
        delete[] wydawca;

        // Allocate new memory for nazwa and wydawca
        nazwa = new char[strlen(rhs.nazwa) + 1];
        wydawca = new char[strlen(rhs.wydawca) + 1];

        // Copy the data from rhs to this object
        strcpy(nazwa, rhs.nazwa);
        strcpy(wydawca, rhs.wydawca);

        // Copy the other fields
        minGraczy = rhs.minGraczy;
        maxGraczy = rhs.maxGraczy;
        czas = rhs.czas;
        skomplikowanie = rhs.skomplikowanie;
        radosc = rhs.radosc;
        fajnosc = rhs.obliczFajnosc();  // Alternatively, you could recalculate using obliczFajnosc()

        // Return *this to support chaining
        return *this;
    }

    // Additional assignment operator overloads to assign a numeric value to fajnosc
    Planszowka& operator=(int liczba) {
        this->fajnosc = std::abs(std::fmod(liczba, 11.0));
        return *this;
    }
    Planszowka& operator=(float liczba) {
        this->fajnosc = std::abs(std::fmod(liczba, 11.0));
        return *this;
    }
    Planszowka& operator=(double liczba) {
        this->fajnosc = std::abs(std::fmod(liczba, 11.0));
        return *this;
    }
    Planszowka& operator=(char liczba) {
        this->fajnosc = std::abs(std::fmod(liczba, 11.0));
        return *this;
    }
};

// Function to load a .txt file and create an array of Planszowka objects.
// Each line in the file should contain: nazwa wydawca minGraczy maxGraczy czas skomplikowanie radosc
Vector<Planszowka> loadPlanszowkiFromFile(const std::string& filename) {
    Vector<Planszowka> planszowki;
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string nazwaStr, wydawcaStr;
        int minGraczy, maxGraczy, czas, skomplikowanie, radosc;
        // Parse the line. Fields are assumed to be whitespace-separated.
        if (!(iss >> nazwaStr >> wydawcaStr >> minGraczy >> maxGraczy >> czas >> skomplikowanie >> radosc)) {
            throw std::runtime_error("Invalid format in line: " + line);
        }
        // Create a Planszowka object (passing c_str() because the constructor expects const char*)
        try {
            Planszowka p(nazwaStr.c_str(), wydawcaStr.c_str(), minGraczy, maxGraczy, czas, skomplikowanie, radosc);
            planszowki.push_back(p);
        } catch (const std::exception& e) {
            std::cerr << "Error creating Planszowka: " << e.what() << "\n";
        }
    }
    return planszowki;
}

// Function to save a vector of Planszowka objects to a file
void savePlanszowkiToFile(Vector<Planszowka>& planszowki, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    for (int i = 0; i < planszowki.size(); i++) {
        file << planszowki[i].getNazwa() << " "
             << planszowki[i].getWydawca() << " "
             << planszowki[i].getMinGraczy() << " "
             << planszowki[i].getMaxGraczy() << " "
             << planszowki[i].getCzas() << " "
             << planszowki[i].getSkomplikowanie() << " "
             << planszowki[i].getRadosc() << "\n";
    }

    file.close();
}
