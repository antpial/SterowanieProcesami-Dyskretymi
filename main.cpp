#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Problem.h"

#define NAZWA_PLIKU "tests/SCHRAGE1.dat"


int main() {
    Problem problem;
    const std::string nazwaPliku = NAZWA_PLIKU;
    
    // Ładowanie danych
    if (problem.zaladujZadaniaPlik(nazwaPliku) == 0) {
        std::cout << "Dane zostały wczytane poprawnie!" << std::endl;
        problem.wyswietlZadania();
    } else {
        std::cerr << "Wystąpił błąd podczas wczytywania danych." << std::endl;
    }

    // Bez sortowania
    std::cout << "\nCzas bez sortowania :" << problem.ileCzasuSort() << "\n";

    // Po Rj
    std::sort(problem.P.begin(), problem.P.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Rj < b.Rj; 
    });
    std::cout << "\nPosortowane po min. Rj:\n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po sortowaniu po min. Rj: " << problem.ileCzasuSort() << "\n";

    // Po Qj
    std::sort(problem.P.begin(), problem.P.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Qj > b.Qj; 
    });
    std::cout << "\nPosortowane po max. Qj:\n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po sortowaniu po max Qj: " << problem.ileCzasuSort() << "\n";


    return 0;
}
