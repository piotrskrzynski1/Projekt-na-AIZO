#pragma once

#include <chrono>

class Timer {
public:
    Timer(); // Konstruktor
    void reset(); // Resetuje timer
    int start(); // Rozpoczyna pomiar czasu
    int stop(); // Kończy pomiar czasu
    [[nodiscard]] long long result() const; // Zwraca czas w milisekundach

private:
    using Clock = std::chrono::high_resolution_clock; //zeby ladniej wygladalo
    std::chrono::time_point<Clock> start_time;
    std::chrono::time_point<Clock> end_time;
    bool running;
};

