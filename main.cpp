#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "Problem.h"

#define NAZWA_PLIKU "tests/SCHRAGE1.dat"


int main() {
    Problem problem;
    const std::string nazwaPliku = NAZWA_PLIKU;
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    
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
    start = std::chrono::high_resolution_clock::now();
    problem.sortPoR();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nPosortowane po min. Rj:\n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po sortowaniu po min. Rj: " << problem.ileCzasuSort() << "\n";
    std::cout << "\nCzas liczenia: " << std::chrono::duration<double, std::milli>(end - start).count() << "[ms]\n";


    // Po Qj
    start = std::chrono::high_resolution_clock::now();
    problem.sortPoQ();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nPosortowane po max. Qj:\n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po sortowaniu po max Qj: " << problem.ileCzasuSort() << "\n";
    std::cout << "\nCzas liczenia: " << std::chrono::duration<double, std::milli>(end - start).count() << "[ms]\n";


    // Wlasne czyli Rj + Qj
    start = std::chrono::high_resolution_clock::now();
    problem.sortWlasne();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nPosortowane wlasne po min(Rj + Qj):\n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po wlasnym sortowaniu po min(Rj+Qj): " << problem.ileCzasuSort() << "\n";
    std::cout << "\nCzas liczenia: " << std::chrono::duration<double, std::milli>(end - start).count() << "[ms]\n";


    // Przeglad Zupelny
    start = std::chrono::high_resolution_clock::now();
    problem.sortPrzegZup();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Najlepsza konfiguracja: \n";
    problem.wyswietlZadania();
    std::cout << "\nCzas po sortowaniu w przegladzie zupelnym: " << problem.ileCzasuSort() << "\n";
    std::cout << "\nCzas liczenia: " << std::chrono::duration<double, std::milli>(end - start).count() << "[ms]\n";


    // SHRAGE
    start = std::chrono::high_resolution_clock::now();
    problem.sortShrage();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nPosortowane za pomoca Shrage: \n";
    problem.wyswietlZadania();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nCzas po sortowaniu za pomoca Shrage: " << problem.ileCzasuSort() << "\n";
    std::cout << "\nCzas liczenia: " << std::chrono::duration<double, std::milli>(end - start).count() << "[ms]\n";



    return 0;
}
